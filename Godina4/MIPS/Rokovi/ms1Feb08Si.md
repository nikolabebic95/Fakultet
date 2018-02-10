# [ms1Feb08SI.doc](http://home.etf.rs/~vm/os/mips/ispit/2008/februar/)

## 1 (4)
**Садржај регистара процесора је: (IP)=200H, (CS)=1000H, (DS)=0007H, (SS)=0003H, (ES)=00006H, (SI)=13H, (BX)=2H, (CX)=9H, (DX)=4H, (SP)=100H, (BP)=9H и дат је следећи сегмент кода који почиње од адресе CS:IP. На датим линијама уписати вриједности које се налазе у регистру АХ након извршаванја инструкције у истом реду? Сматрати да се инструкције извршавају једна за другом.**

**Напомена 1 : Садржај меморијске локације (бајта) једнак је вриједности нижег бајта адресе те локације.**

Isto kao [ovde](ms1Feb08.md)

## 2 (4)
**Потребно је у асемблеру за микропроцесор 8086 написати if-then-else, гдје је услов OP1 > OP2 (OP1 и OP2 су симболичке адресе операнада у меморији). Додатни проблем је што су блокови у then и else секцијама већи од 128B.**

Isto kao [ovde](ms1Feb08.md)

## 3 (4)
**Објаснити чему служи и како се користи флег AF. Навести примјер у којем тај флег добија вриједност 1 и објаснити како се то користи.**

Taj fleg ima istu ulogu kao Carry flag, samo što indikuje kada se prenos desio iz najniža 4 bajta registra. Primer:

```asm
; ...
mov al, 10  ; al je 0x0A
add al, 6   ; al postaje 16, što je 0x10, desio se prenos
            ; i adjust flag se pali
; ...
```

Ovo može da se koristi kod packed BCD instrukcija, gde se dve cifre čuvaju u donjih i gornjih 4 bita jednog bajta. Tada je bitno da znamo kad se desio prenos između BCD cifara, da bismo mogli da održimo konzistentan BCD broj.

## 4 (4)
**Објаснити како микропроцесор чита ријечи у зависности од адресе и образложити разлог за то. Навести вриједности релевантних сигнала.**

Isto kao treće pitanje [ovde](ms1Feb08.md)

## 5 (4)
**Чему служе и да ли се увијек користе линије CAS код контролера прекида?**

Koriste se samo u master/slave režimu, kada imamo više kaskadno povezanih kontrolera prekida. U ovom slučaju, master kontroler ove linije koristi kao izlazne, a slave kontroleri kao ulazne. U slučaju da se desi neki prekid, master po ovim linijama šalje ID selektovanog slejva, a onda taj slejv može da pošalje adresu svoje prekidne rutine preko DATA linija.

## 6 (4)
**Када је и зашто при читању потребно лечовати вриједност бројача у 8254?**

Isto kao četvtro pitanje [ovde](ms1Feb08.md)

## 7 (4)
**Објаснити чему служе и како се генеришу линије RxRDY и TxRDY (серијски порт – 8251).**

RxRDY je linija kojom serijski port može da javi da je primio podatak, i da je spreman da taj podatak procesor pročita.

TxRDY je linija kojom serijski port može da javi da je spreman da od procesora prihvati podatak koji treba da pošalje.

## 8 (4)
**Колико портова има микроконтролер 8051 и која је њихова намјена?**

Nije rađeno

## 9 (4) 
**Навести модове серијског порта присутног у микроконтролеру 8051 и објаснити.**

Nije rađeno

## 10 (4)
**Какву везу пружа магистрала PCI-Express у погледу ширине података, броја крајњих тачака које могу бити повезане и могућности слања у оба смјера?**

Nije rađeno
