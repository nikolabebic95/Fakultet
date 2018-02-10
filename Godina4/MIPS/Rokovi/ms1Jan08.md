# [ms1Jan08.doc](http://home.etf.rs/~vm/os/mips/ispit/2008/januar/)

## 1 (4) 
**Садржај регистара процесора је: (IP)=200H, (CS)=1000H, (DS)=0004H, (SS)=0009H, (ES)=0007H, (SI)=4H, (BX)=3H, (CX)=5H, (DX)=2H, (SP)=100H, (BP)=6H и дат је следећи сегмент кода који почиње од адресе CS:IP. На датим линијама уписати вриједности које се налазе у регистру АХ након извршаванја инструкције у истом реду? Сматрати да се инструкције извршавају једна за другом.**

**Напомена 1 : Садржај меморијске локације (бајта) једнак је вриједности нижег бајта адресе те локације.**

```
xor AX, AX          ; AX = 0000H
add AX, [BX]        ; AX = 4443H
add AL, [BP][SI]    ; AX = 44DDH
add AX, [BX+4][SI]  ; AX = 9128H

```

## 2 (4)
**Написати код који у низу NIZ који има 100 елемената проналази прво појављивање знака који се налази на локацији ZNAK. Користити одговарајућу LOOP наредбу.**

```asm
mov ax, SEG NIZ
mov ds, ax
mov si, ZNAK
mov al, es:[di]
mov si, OFFSET NIZ
dec si
mov cx, 100

loop:
inc si
cmp [si], al
loopne loop
; ...
```

## 3 (4) 
**Објаснити генерисање сигнала READY. Објаснити како се одређује колико је WAIT стања убачњно.**

Signal READY indikuje da read ili write ciklus može da se završi, tj. da je memorija završila svoj posao. Ubacuje se 0 ili više WAIT stanja, u zavisnosti od toga koliko je memorija spora. U četvrto stanje se prelazi tek kada je na početku prethodnog stanja READY signal upaljen. Ukoliko je on upaljen odmah u trećem stanju, neće biti ubačeno nijedno WAIT stanje, a u svim ostalim slučajevima će biti ubacivana WAIT stanja dok se u nekom od njih ne upali READY signal

## 4 (4)
**Објаснити зашто није увијек могуће за 8259А користити AEOI мод рада**

Nije moguće kada postoje ugnježdeni prekidi. AEOI briše ISR bit prekida čim se pozove prekidna rutina, i ako postoje ugnježdeni prekidi sada bi mogao da se prihvati prekid nižeg prioriteta, a ne bi trebalo

## 5 (4) 
**Објаснити зашто се код верзије микроконтролера 8051 која има 256B интерне RAM меморије не може на исти начин приступати нижих и виших 128B. Која је разлика?**

Nije rađeno

## 6 (4) 
**Шта је Inquire цикус? Нацртати таблицу прелаза стања.**

Nije rađeno

## 7 (4) 
**Објаснити када и зашто је предиктор са два бита бољи од предиктора са једним битом?**

U slučaju da se neka petlja ponavlja u drugoj petlji, za uslov druge petlje je bolje koristiti prediktor sa dva bita, zato što će promašiti samo na izlasku iz petlje, a prediktor sa jednim bitom bi promašio na izlasku, pa bi ponovo promašio na sledećem ulasku u istu petlju, jer je zapamtio samo poslednji rezultat.

## 8 (4) 
**Шта је Loop unrolling?**

To je tehnika optimizacije petlji u kojoj se smanjuje vreme izvšavanja programa. Ukoliko postoji petlja čija iteracija traje kratko, postoji veliki overhead na proveru uslova kraja petlje i skok na početak. U ovom slučaju možemo u jednu iteraciju nove petlje staviti više iteracija stare petlje, tako da ređe radimo proveru uslova kraja i skok na početak. Ukoliko ne znamo unapred broj iteracija, moramo i da umetnemo pre petlje proveru da li stara petlja ima dovoljan broj iteracija da može da se izvrši bar jedna iteracija nove petlje, i takođe pre ili posle petlje moramo umetnuti kod koji proverava da li je broj iteracija originalne petlje deljiv brojem iteracija nove petlje. Ukoliko nije, pre ili posle se moraju izvršiti preostale iteracije. Ovo uvodi dodatan overhead, ali u slučaju dovoljno velike petlje, veća je korist od smanjenja broja skokova i provera uslova kraja u petlji, nego što je šteta od dodatnog posla van petlje.

## 9 (4) 
**Нацртати stride based предиктор вриједности. Када је овакав предиктор посебно погодан и како?**

Ima slika na [06.Dps.doc](http://home.etf.rs/~vm/os/mips/predavanja/micr/)

Ovakav prediktor je posebno pogodan u petljama, kada se nešto radi sa indeksom iteracije.

## 10 (4) 
**Које су битне особине подсистема у бежичним сензорским мрежама?**

Nije rađeno
