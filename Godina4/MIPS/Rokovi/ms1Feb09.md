# [ms1Feb09.doc](http://home.etf.rs/~vm/os/mips/ispit/2009/IR_februar/)

## 1 (4) 
**Садржај регистара процесора је: (IP)=200H, (CS)=1000H, (DS)=0004H, (SS)=000BH, (ES)=0007H, (SI)=34H, (BX)=28H, (CX)=133H, (DX)=4H, (SP)=102H, (BP)=76H и дат је следећи сегмент кода који почиње од адресе CS:IP. На датим линијама уписати вриједности које се налазе у регистру АХ након извршаванја инструкције у истом реду? Сматрати да се инструкције извршавају једна за другом**

**Напомена 1 : Садржај меморијске локације (бајта) једнак је вриједности нижег бајта адресе те локације.**

```asm
xor AX, AX          ; AX = 0000H
add AX, [BX]        ; AX = 6968H
add AL, [BP][SI]    ; AX = 69C2H
add AX, [BX+4][SI]  ; AX = 0B62H
```

## 2 (4)
**Чему служи и како се користи бит помоћног преноса код микропроцесора 8086?**

Isto kao treće pitanje [ovde](ms1Feb08Si.md)

## 3 (4)
**Пројектује се неки систем заснован на микропроцесору 8086 и додају се три контролера прекида, један master (М), један slave на улаз број 1 master-а (S1) и други slave на улаз 7 master-a (S7). Ако су до тог тренутка били слободни улази у IVT почев од 44, додијелити најмање могуће бројеве улаза, тако да се прво додјељују master-u M, па slave-u S1 и на крају slave-u S7? Приказати који ће се улази стварно користити.**

M će da dobije ulaze 44, 45, 46, 47, 48, 49 i 50  
S1 će da dobije ulaze 51, 52, 53, 54, 55, 56 i 57  
S7 će da dobije ulaze 58, 59, 60, 61, 62, 63 i 64

Stvarno će se koristiti svi osim 45 i 50

## 4 (4) 
**Ако је такт неког бројача реда 1Hz, да ли је могуће прочитати вриједност бројача без његовог заустављања и лечовања? Прецизно и кратко објаснити**

Koliki god da je takt, ovo nije moguće, jer možda brojač menja vrednost baš u trenutku kada čitamo, pa ćemo možda dobiti nedefinisanu vrednost čitanjem.

## 5 (4)
**Ако се пише прекидна рутина која се позива када се прими податак преко серијског порта микроконтролера 8051, о чему се мора водити рачуна, а што није случај са прекидним рутинама за остале периферије?**

Nije rađeno

## 6 (4) 
**Да ли се у Pentium процесору за одређене дијелови меморије за податке може забранити кеширање? Ако да, објаснити како.**

Nije rađeno

## 7 (4)
**Да ли има смисла планирати да се даља повећања броја транзистора утроше за повећање броја паралелних токова у SS (Super Scalar) процесору како би се повећала брзина процесора? Прецизно и кратко образложити одговор.**

Nema, jer se neće dovoljno isplatiti, jer je onda potreban mnogo veći registarski fajl kako bi još jedna nit mogla da čuva svoje podatke, a svakako bi niti imale problem prilikom paralelnih pristupa globalnim podacima, i izbacivale bi jedna drugoj podatke iz keša više nego što je to sada slučaj.

## 8 (4) 
**Нацртати шему 2-битног предиктора у два нивоа.**

Ima slika na [05.Bps.doc](http://home.etf.rs/~vm/os/mips/predavanja/micr/)

## 9 (4)
**Како се дијеле технике за превазилажење негативних ефеката зависности инструкција по подацима? Са по једном реченицом објаснити сваку групу**

- Kombinovanje zavisnih instrukcija u jednu
- Run time menjanje redosleda izvršavanja instrukcija kako bi se uvek izvršavale instrukcije koje imaju sve svoje podatke
- Spekulativno izvršavanje zavisnih instrukcija, uz predviđanje podataka koji još nisu izračunati

## 10 (4) 
**Која су два основна типа multithreading-a? Која је основна разлика између та тва типа?**

- Simultaneous multithreading
- Temporal multithreading

Prva tehnika podrazumeva postojanje više niti koje se izvršavaju na istom jezgru, tako što se koristi ILP kako bi različiti delovi jezgra izvršavali instrukcije iz više nezavisnih niti.  

Druga tehika podrazumeva da jedno jezgro u nekim vremenskim intervalima menja kontekst, i izvršava više niti konkurentno.




