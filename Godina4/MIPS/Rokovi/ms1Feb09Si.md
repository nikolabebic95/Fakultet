# [ms1Feb09.doc](http://home.etf.rs/~vm/os/mips/ispit/2009/SI_februar/)

## 1 (4) 
**Садржај регистара процесора је: (IP)=200H, (CS)=1000H, (DS)=0004H, (SS)=000BH, (ES)=0007H, (SI)=34H, (BX)=28H, (CX)=15H, (DX)=4H, (SP)=102H, (BP)=76H и дат је следећи сегмент кода који почиње од адресе CS:IP. На датим линијама уписати вриједности које се налазе у регистру АХ након извршаванја инструкције у истом реду? Сматрати да се инструкције извршавају једна за другом**

**Напомена 1 : Садржај меморијске локације (бајта) једнак је вриједности нижег бајта адресе те локације.**

Isto kao [ovde](ms1Feb09.md)

## 2 (4)
**Чему служи и како се користи бит помоћног преноса код микропроцесора 8086?**

Isto kao treće pitanje [ovde](ms1Feb08Si.md)

## 3 (4) 
**Објаснити инструкцију ROR.**

Instrukcija `ROR` vrši rotaciju registra desno. Radi tako što pomera sve bite osim najnižeg za po jedno mesto niže, a najniži bit umeće na mesto bita najviše težine, i u CF. Na ostale flegove ne utiče.

## 4 (4)
**На асемблеру микропроцесора 8086 написати рекурзивну функцију која рачуна суму првих N елемената.**

```asm
sum PROC NEAR
    push bp
    mov bp, sp

    mov ax, [bp+4]
    cmp ax, 0
    jne skip

    mov sp, bp
    pop bp
    ret

    skip:
    mov cx, ax
    dec ax
    push ax
    call sum
    add sp, 2
    add ax, cx
    
    mov sp, bp
    pop bp
    ret
sum ENDP
```

## 5 (4) 
**Објаснити сигнале ALE и DT/R.**

ALE je upaljen kada se na magistrali AD nalazi adresa, koja treba da se lečuje. Lečevi će onda signal ALE iskoristiti kao svoj LOAD signal.  

DT/R signal je upaljen kada se na magistrali AD nalazi podatak, a ne adresa

## 6 (4)
**Пројектује се неки систем заснован на микропроцесору 8086 и додају се три контролера прекида, један master (М), један slave на улаз број 1 master-а (S1) и други slave на улаз 7 master-a (S7). Ако су до тог тренутка били слободни улази у IVT почев од 44, додијелити најмање могуће бројеве улаза, тако да се прво додјељују master-u M, па slave-u S1 и на крају slave-u S7? Приказати који ће се улази стварно користити.**

Isto kao treće pitanje [ovde](ms1Feb09.md)

## 7 (4)
**Да ли ће бити пријављена нека грешка ако док процесор још није прочитао претходно примљени бајт, почне пријем следећег бајта? Образложити одговор.**

Neće, samo će se preko tog podatka prepisati novi

## 8 (4) 
**Ако је такт неког бројача реда 1Hz, да ли је могуће прочитати вриједност бројача без његовог заустављања и лечовања? Прецизно и кратко објаснити**

Isto kao četvrto pitanje [ovde](ms1Feb09.md)

## 9 (4) 
**Колико највише DMA контролера може да се повеже у један систем заснован на микропроцесору 8086? Образложити.**

Nije ograničen broj, jer se kontroleri mogu kaskadno povezivati

## 10 (4) 
**Ако се пише прекидна рутина која се позива када се прими податак преко серијског порта микроконтролера 8051, о чему се мора водити рачуна, а што није случај са прекидним рутинама за остале периферије?**

Nije rađeno
