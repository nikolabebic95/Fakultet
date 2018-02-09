# [primer_kolokvijuma.doc](http://home.etf.rs/~vm/os/mips/ispit/2012/)

## 1 (4)
**Садржај регистара процесора је: (IP)=200H, (CS)=1000H, (DS)=0006H, (SS)=006CH, (ES)=00002H, (SI)=4H, (BX)=12H, (CX)=31H, (DX)=16H, (SP)=114H, (BP)=116H и дат је следећи сегмент кода који почиње од адресе CS:IP. Који је садржај регистра АХ након извршавања сваке од следећих инструкција?**

**Напомена 1 : Садржај меморијске локације (бајта) једнак је вриједности нижег бајта адресе те локације.**  

```asm
pop AX                  ; AX = D5D4H, SP = 112H
add AX, [BX]            ; AX = 4946H
add AL, [BP][SI]        ; AX = 49AAH
add AX, [BX+19h][SI]    ; AX = FF5EH
```

## 2 (4)
**Објаснити чему служе и како се користе сигнали DT/R и DEN, који се појављују код микропроцесора 8086.**

Ovi signali se koriste kod bilo kakve operacije koja upisuje ili čita memoriju. Signal DT/R označava smer prenosa podataka (1 - od procesora, 0 - ka procesoru). Signal DEN označava da je u toku ovakva operacija, i kada je aktivan to znači da se AD linije koriste kao DATA magistrala.

## 3 (4)
**Нека 8-битна периферија повезана је на виших 8 линија дата магистрале процесора. Периферија захтјева 4 адресе и повезана је тако да јој се приступа кроз улазно/излазни адресни простор. Које од понуђених група адреса би могле бити додјељене наведеној периферији како би се препознавање адреса свело на коњункцију у којој учествују адресне линије и њихове инвертоване вриједности? Тачне одговоре заокружити, а за сваки нетачан дати бар једно објашњење зашто дати скуп адреса није могуће додјелити поменутој периферији.**

```
a)    б)     в)    г)    д)
1000h 10001h 1008h 1009h 1005h
1002h 10003h 100Ah 100Bh 1007h
1004h 10005h 100Ch 100Dh 1009h
1006h 10007h 100Eh 100Fh 100Bh
```
Odgovori:
- A - Netačno jer je periferija povezana na viših 8 linija DATA magistrale, to znači da nulti bajt svih adresa mora da bude 1.
- B - Tačno
- V - Isto kao A
- G - Tačno
- D - Netačno jer se ove 4 adrese razlikuju na više od 2 bita (konkretno, razlikuju se na bitima 3, 2 i 1 poslednjeg bajta). Ukoliko želimo konjukciju adresnih linija i invertovanih vrednosti, 4 adrese dodeljene periferiji moraju da se međusobno razlikuju na tačno dva bita.

## 4 (2)
**Шта је P флег и како се рачуна његова вриједност?**

To je bit u programskoj statusnoj reči koji određuje da li rezultat poslednje izvršene instrukcije ima paran ili neparan broj jedinica u svojoj bitskoj reprezentaciji. U slučaju parnog broja je `P == 0`, a u slučaju neparnog broja je `P == 1`.

## 5 (4)
**Навести и са по једном реченицом објаснити фазе од којих се састоји један машински циклус на магистрали микропроцесора 8086. Посматра се циклус најкраћег могућег трајања.**

1. Postavlja se smer prenosa podataka, postavlja se adresa, i pred kraj faze se lečuje postavljena adresa.
2. Postavlja se podatak/magistrala se oslobađa za podatak, postavlja se DEN signal kako bi magistrala bila označena kao data magistrala, i pred kraj se postavlja WR/RD signal.
3. READY signal je 1, ne umeće se nijedno stanje čekanja.
4. Ukoliko je READ ciklus, dohvata se podatak, DEN signal se gasi.

## 6 (4)
**Навести све могуће изворе прекида микропроцесора 8086 и за сваки објаснити како се долази до броја улаза у IVT.**

- Spoljašnji
    - Maskirajući: Ciklusom dohvatanja broja ulaza sa periferije - broj koji se dohvati se pomnoži sa veličinom adrese prekidne rutine (4) i to je adresa prekidne rutine
    - Nemaskirajući: Broj ulaza je fiksan
- Unutrašnji: Broj ulaza je fiksan (osim u slučaju INT)
    - U slučaju INT prekida broj ulaza je u samoj instrukciji

## 7 (4)
**Која је логичка функција кола приказаног на слици. Приказати процес закључивања.**

Logička funkcija je OR. Ako se na oba ulaza stave neaktivni signali, oba tranzistora gore će provoditi struju, tako da će GATE gornjeg desnog tranzistora biti aktivan, što znači da on neće provoditi struju, a donji desni tranzistor će voditi struju, tako da će izlaz biti neaktivan. Ako je bilo koji (ili oba) od ulaza aktivan, odgovarajući tranzistor gore neće provesti struju, a odgovarajući tranzistor dole hoće, tako da na GATE desnih tranzistora će biti neaktivan signal, a u tom slučaju gornji provodi a donji ne. Tako dobijamo da je na izlazu aktivan signal.
