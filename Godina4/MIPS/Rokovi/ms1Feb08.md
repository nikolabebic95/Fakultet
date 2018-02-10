# [ms1Feb08.doc](http://home.etf.rs/~vm/os/mips/ispit/2008/februar/)

## 1 (4)
**Садржај регистара процесора је: (IP)=200H, (CS)=1000H, (DS)=0007H, (SS)=0003H, (ES)=00006H, (SI)=13H, (BX)=2H, (CX)=9H, (DX)=4H, (SP)=100H, (BP)=9H и дат је следећи сегмент кода који почиње од адресе CS:IP. На датим линијама уписати вриједности које се налазе у регистру АХ након извршаванја инструкције у истом реду? Сматрати да се инструкције извршавају једна за другом.**

**Напомена 1 : Садржај меморијске локације (бајта) једнак је вриједности нижег бајта адресе те локације.**

```asm
xor AX, AX          ; AX = 0000H
add AX, [BX]        ; AX = 7372H
add AL, [BP][SI]    ; AX = 73BEH
add AX, [BX+8][SI]  ; AX = B655H
```

## 2 (4)
**Потребно је у асемблеру за микропроцесор 8086 написати if-then-else, гдје је услов OP1 > OP2 (OP1 и OP2 су симболичке адресе операнада у меморији). Додатни проблем је што су блокови у then и else секцијама већи од 128B.**

```asm
; ...
mov ax, OP1
mov bx, OP2
mov ax, [ax]
mov bx, [bx]
cmp ax, bx
jgt then_branch
jmp else_branch
then_branch: ; ...
jmp end_branch
else_branch: ; ...
end_branch: ; ...

```

## 3 (4)
**Објаснити како микропроцесор чита ријечи у зависности од адресе и образложити разлог за то. Навести вриједности релевантних сигнала.**

Ukoliko je niži bajt reči na parnoj adresi, adrese nižeg i višeg bajta se razlikuju samo u poslednjem bitu, tako da procesor može da pročita tu vrednost u jednom ciklusu čitanja. Ukoliko je niži bajt na neparnoj adresi, tada se adrese razlikuju u bar još jednom bitu, osim poslednjeg. U ovoj situaciji se čitanje reči posmatra kao potpuno nezavisno čitanje dva bajta, i to se vrši u dva ciklusa na magistrali. Za prvi slučaj su (A0,BHE)==(0,0), a za drugi slučaj su (A0,BHE)==(1,0).

## 4 (4)
**Када је и зашто при читању потребно лечовати вриједност бројача у 8254?**

Potrebno je ako želimo da pročitamo vrednost brojača, a da pritom brojač neometano radi. Ukoliko bismo čitali običnom READ operacijom, brojač mora biti zaustavljen kako ne bismo imali nedefinisan rezultat čitanja, koji može da se dogodi u slučaju da u istom trenutku kada čitamo, brojač menja vrednost.

## 5 (4)
**Навести модове серијског порта присутног у микроконтролеру 8051 и објаснити.**

Nije rađeno

## 6 (4)
**Које су три основне методе за повећање ILP-a? Дати кратак опис свих**

- Superskalarni procesori - procesori koji izvršavaju više od jedne (nezavisne) instrukcije u jednom trenutku. Moguće je da te instrukcije budu instrukcije iste niti, ili instrukcije više različitih niti (u ovom slučaju, ovo se drugačije zove i hyperthreading ili simultaneous multithreading).
- Pipeline - Dok se izvršava druga faza prve instrukcije, izvršava se prva faza prve, a dok se izvršava treća faza prve, 
izvršava se druga faza druge i treća faza prve instrukcije.
- Very large instruction word - Posebne instrukcije u kojima je moguće specificirati više od jedne osnovne instrukcije, a onda se one izvršavaju u paraleli.

## 7 (4)
**Нацртати шему Pshare предиктора и извести формулу за цијену коштања тог предиктора?**

Ima slika na [05.Bps.doc](http://home.etf.rs/~vm/os/mips/predavanja/micr/), cena je _m * 2<sup>n</sup> + 2<sup>m + 1</sup>_

## 8 (4)
**Које су два основна приступа у дизајнирању спекулативних инструкција?**

- Compile time - kompajler radi predikciju grananja i spekulaciju, hardver samo pomogne u oporavku ukoliko predikcija nije bila tačna.
- Run time - hardver radi i predikciju i spekulaciju, kompajler generiše kod kao što bi i inače.

## 9 (4)
**Објаснити limited directory протоколе**

To su _directory_ protokoli kod kojih katalog ne zauzima **O(MP)** prostora, nego manje, tako što se smanjuje **P** dimenzija (**M** dimenzija predstavlja broj blokova koji se dele, **P** dimenzija broj procesora koji mogu da dele memoriju). U ovom slučaju, moguće je smanjiti **P** dimenziju na nekoliko načuna, pomoću Dir<sub>_i_</sub>**X** protokola. Ovi protokoli rade tako što ne čuvaju informacije o svim mogućim procesima, već imaju fiksan broj pointera koji služe da indikuju da neki procesor drži određen blok. Parametar _i_ predstavlja broj pointera koji se koriste, a _X_ predstavlja tehniku koja se koristi u slučaju prekoračenja broja pointera.

## 10 (4)
**Навести основну подјелу протокола рутирања у бежичним сензорским мрежама према начину идентификације чворова. Дати кратак опис сваке врсте.**

Nije rađeno
