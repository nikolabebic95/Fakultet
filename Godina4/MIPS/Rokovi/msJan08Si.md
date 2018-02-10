# [ms1Jan08.doc](http://home.etf.rs/~vm/os/mips/ispit/2008/januar/)

## 1 (4)
**Садржај регистара процесора је: (IP)=200H, (CS)=1000H, (DS)=0005H, (SS)=0009H, (ES)=00004H, (SI)=4H, (BX)=7H, (CX)=3H, (DX)=8H, (SP)=100H, (BP)=9H и дат је следећи сегмент кода који почиње од адресе CS:IP. На датим линијама уписати вриједности које се налазе у регистру АХ након извршаванја инструкције у истом реду? Сматрати да се инструкције извршавају једна за другом.**

**Напомена 1 : Садржај меморијске локације (бајта) једнак је вриједности нижег бајта адресе те локације**

```asm
xor AX, AX          ; AX = 0000H
add AX, [BX]        ; AX = 5857H
add AL, [BP][SI]    ; AX = 58F4H
add AX, [BX+4][SI]  ; AX = B953H
```

## 2 (4) 
**Кратко и прецизно објаснити подршку микропроцесора 8086 коју пружа при обради низова.**

Postoji instrukcija `rep`, koja može da ponavlja određenu instrukciju nekoliko puta. Broj puta koji se ponavlja instrukcija je definisan CX registrom. Takođe, ova instrukcija može imati sufikse, koji indikuju kada još može da se izađe iz ciklusa ponavljanja, na isti način kao što se to radi sa loop instrukcijom. Instrukcije koje instrukcija `rep` može da ponavlja služe za pretraživanje, kopiranje, poređenje ili inicijalizaciju nizova.

## 3 (4) 
**Објаснити наредбе LDS и XCHG и приказати како се наредба XCHG ако је потрбно да се изврши над два операнда (бајта) који се налазе у меморији на адресама OP1 и OP2.**

Naredba LDS upisuje duplu reč iz memorije u zadati registar, i registar DS. U zadatom registru se nalazi prva reč, a u DS druga reč.  

Naredba XCHG menja vrednosti svoja dva operanda

```asm
mov ax, OP1
mov bl, [ax]
mov cx, OP2
xchg bl, [cx]
mov [ax], bl
```

## 4 (4) 
**Објаснити сигнале ALE и READY.**

Signal ALE indikuje da je trenutno na AD magistrali adresa, koja treba da se upiše u lečeve. Ovaj signal je vezan na load signal lečeva

Signal READY indikuje da memorija nije trenutno zauzeta

## 5 (4) 
**У неком систему су заузети сви улази у IVT од почетка до броја 50 (улаз број 50 је заузет). Остали су слободни. У систем је потребно додати још два контролера прекида. Које улазе у IVT им треба додијелити, ако претпоставимо да да им се додјељују најмањи могући бројеви упаза? Ако улазе за прекиде на првом означимо са А0..А7 и на другом B0..B7, и други контролер повежемо на А5 улаз првог, за сваки улаз написати одговарајући број улаза у IVT у којем се налази адреса прекидне рутине.**

A0..A7 će da budu ulazi 56-63  
B0..B7 će da budu ulazi 64-71

Ulaz 61 neće biti iskorišćen

## 6 (4) 
**Шта може да буде проблем при читању вриједности бројача из тајмерa? Како се рјешава тај проблем?**

Možda se vrednost tajmera menja upravo u trenutku čitanja, tako da ćemo možda dobiti nekonzistentnu vrednost.  
Problem se rešava tako što možemo da lečujemo trenutnu vrednost bez ometanja brojanja, pa pročitamo zalečovanu, ili, ako nam brojanje više nije bitno, zaustavimo brojač i pročitamo vrednost.

## 7 (4) 
**Навести и објаснити грешке које серијски порт 8251 може да детектује.**

- Parity error - Primljen podatak nije tačan, jer se mu se checksum ne poklapa sa bitom parnosti.
- Overrun error - Primljen podatak nije niko pročitao, a port je počeo da prima novi podatak
- Frame error - Stop bit nije došao u trenutku kada je trebalo da dođe.

## 8 (4) 
**Кратко и прецизно објаснити како се код микроконтролера 8051 при обрађивању захтјева за прекид одређује адреса прекидне рутине и како се код прекидне рутине смјешта у меморију у зависности од величине? Није потрбно наводити никакве конкретне вриједности нити редослијед прекидних рутина**

Nije rađeno

## 9 (4) 
**Објаснити ограничење у погледу дужине трајања импулса РЕСЕТ сигнала код микроконтролера 8051 које тај сигнал мора да задовољи да би био препознат.**

Nije rađeno

## 10 (4) 
**Какву везу пружа магистрала PCI-Express у погледу ширине података, броја крајњих тачака које могу бити повезане и могућности слања у оба смјера?**

Nije rađeno
