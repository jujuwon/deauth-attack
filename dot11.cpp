#include "dot11.h"

void DeauthHdr::radioInit() {
    revision_ = 0x0;
    pad_ = 0x0;
    len_ = 0x0c;
    present_ = 0x00008004;
    dum_ = 0x0;
}

void DeauthHdr::dotInit() {
    ver_ = 0x0;
    type_ = 0x0;
    subtype_ = 0xc;
    flags_ = 0x0;
    duration_ = 0x0;
    nums_ = 0x0;
    reasonCode_ = ReceivedFromNonAssociatedSTA;
}