## Deauth Attack

π‘ Station μ°κ²° κ°μ  μ’λ£ νλ‘κ·Έλ¨
<br>
<br>
### Deauth Attack
802.11 Deauthenfication ν¨ν·μ λ°μμμΌ κΈ°μ‘΄μ μ°κ²°μ κ°μ μ μΌλ‘ λμ μ μλ€. μ΄λ₯Ό Deauth Attack μ΄λΌ νλ€.
<br>
<br>
### Auth Attack
νΉμ  Station κ° AP μ μ°κ²°λμ΄ μλ μνμμ ν΄λΉ Station κ³Ό λκ°μ Mac address λ₯Ό κ°μ§κ³  λμΌν AP μ μ°κ²°μ μλνλ©΄

κΈ°μ‘΄ Station μ μ°κ²°μ΄ λκΈ°κ² λλ€. μ΄λ₯Ό Authentication Attack μ΄λΌ νλ€.
<br>
<br>
### μ€ν
```sh
$ make
$ syntax : deauth-attack <interface> <ap mac> [<station mac>] [-auth]
$ sample : deauth-attack mon0 00:11:22:33:44:55 66:77:88:99:AA:BB
```
