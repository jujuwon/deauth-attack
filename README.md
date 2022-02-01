## Deauth Attack

💡 Station 연결 강제 종료 프로그램
<br>
<br>
### Deauth Attack
802.11 Deauthenfication 패킷을 발생시켜 기존의 연결을 강제적으로 끊을 수 있다. 이를 Deauth Attack 이라 한다.
<br>
<br>
### Auth Attack
특정 Station 가 AP 에 연결되어 있는 상태에서 해당 Station 과 똑같은 Mac address 를 가지고 동일한 AP 에 연결을 시도하면

기존 Station 의 연결이 끊기게 된다. 이를 Authentication Attack 이라 한다.
<br>
<br>
### 실행
```sh
$ make
$ syntax : deauth-attack <interface> <ap mac> [<station mac>] [-auth]
$ sample : deauth-attack mon0 00:11:22:33:44:55 66:77:88:99:AA:BB
```
