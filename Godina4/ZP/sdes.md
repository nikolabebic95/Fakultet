# Uputstvo za SDES Algoritam

## Generisanje ključa

1) 10bit ključ se propusti kroz PC1
2) Uradi se rotacija rezultata ulevo, ali **na polovinama**
3) Ključ za prvu rundu se dobija propuštanjem rezultata kroz PC2
4) Uradi se rotacija rezultata tačke _2_ ulevo, takođe **na polovinama**
5) Ključ za drugu rundu se dobija propuštanjem rezultata tačke _4_ kroz PC2

### Primer:

Svi indeksi počinju od 1

|Identifikator|           Vrednost          | 
|-------------|-----------------------------|
|    Ključ    |`0b10111101`                 |
|     PC1     |3, 5, 2, 7, 4, 10, 1, 9, 8, 6|
|     PC2     |6, 3, 7, 4, 8, 5, 10, 9      | 

Rotacija se u tačkama _2_ i _4_ radi za jedno mesto

---

1) Propuštanje ključa kroz PC1:
    - Prvi bit rezultata je treći bit ključa
    - Drugi bit rezultata je peti bit ključa
    - ...
    - Rezultat je `0b1000001100`
2) Rotacija rezultata ulevo za jedno mesto
    - Leva polovina prethodnog rezultata je `0b10000`
    - Desna polovina prethodnog rezultata je `0b01100`
    - Novonastala leva polovina je `0b00001`
    - Novonastala desna polovina je `0b11000`
    - Kada se spoje polovine dobije se rezultat `0b0000111000`
3) Propuštanje prethodnog rezultata kroz PC2
    - Prvi bit rezultata je šesti bit rezultata tačke _2_
    - ...
    - Ključ za prvu rundu je `0b10100100`
4) Rotacija rezultata tačke _2_ ulevo za jedno mesto
    - Početna leva polovina je `0b00001`
    - Početna desna polovina je `0b11000`
    - Rezultat je `0b0001001100`
5) Propuštanje prethodnog rezultata kroz PC2
    - Ključ za drugu rundu je `0b10010010`

## Struktura jedne runde

Runda je funkcija koja preslikava 8bit ulazni podatak u 8bit izlazni podatak

1) Ulazni podatak se podeli na dve polovine, desnu i levu
2) Desna polovina se propusti kroz E tako da se proširi sa 4 na 8 bita.
3) 8 bita koji su dobijeni kao rezultat tačke _2_ se `xor`-uju sa 8bit ključem runde
4) 8bit rezultat tačke _3_ se podeli na levu i desnu polovinu
5) Leva polovina se propusti kroz S1, tako što se prvi i poslednji bit koriste kao indeks vrste, a unutrašnja dva bita kao indeks kolone
6) Desna polovina rezultata tačke _4_ se propusti kroz S2, kao što se leva propušta kroz S1 u tački _5_
7) Rezultati tačaka _5_ i _6_ se spoje i propuste kroz P
8) Rezultat tačke 7 se `xor`-uje sa levom polovinom dobijenom u tački _1_
9) Rezultat runde se napravi tako što se nadovežu desna polovina dobijena u tački _1_ i rezultat tačke _8_

### Primer

Svi indeksi počinju od 1

|Identifikator|Vrednost              | 
|-------------|----------------------|
|Ulaz runde   |`0b01111110`          |
|E            |4, 1, 2, 3, 2, 3, 4, 1|
|P            |2, 4, 3, 1            | 
|Ključ runde  |`0b10100100`          | 

Indeksi S1 i S2 počinju od 0

S1:

| | | | |
|-|-|-|-|
|1|0|3|2|
|3|2|1|0|
|0|2|1|3| 
|3|1|0|2|

S2:

| | | | |
|-|-|-|-|
|0|1|2|3|
|2|0|1|3|
|3|0|1|2| 
|2|1|0|3|

---

1) Podela ulaznog podatka na dve polovine
    - Ulazni podatak je `0b01111110`
    - Leva polovina je `0b0111`
    - Desna polovina je `0b1110`
2) Propuštanje desne polovine kroz E
    - Prvi bit rezultata je četvrti bit desne polovine
    - Drugi bit rezultata je prvi bit desne polovine
    - ...
    - Rezultat je `0b01111101`
3) `XOR` sa ključem runde
    - `0b01111101` - rezultat prethodne operacije
    - `0b10100100` - ključ runde
    - `0b11011001` - rezultat `xor`-a
4) Podela rezultata tačke _3_ na polovine
    - `0b1101` - leva
    - `0b1001` - desna
5) Propuštanje leve polovine kroz S1
    - Prvi i poslednji bit su `0b11`, što je vrednost 3
    - Unutrašnja dva bita su `0b10`, što je vrednost 2
    - Traži se element u S1 na indeksu `[3,2]`
    - Traženi element je 0, što je `0b00`
6) Propuštanje desne polovine rezultata tačke _4_ kroz S2
    - Indeks je `[3,0]`
    - Traženi element je 2, što je `0b10`
7) Spajanje tačaka _5_ i _6_ i propuštanje kroz P
    - Rezultat spajanja je `0b0010`
    - Kad se propusti kroz P dobije se `0b0010`
8) `XOR` sa levom polovinom iz tačke _1_
    - `0b0010` - rezultat prethodne operacije
    - `0b0111` - leva polovina iz tačke _1_
    - `0b0101` - rezultat `xor`-a
9) Pravljenje rezultata runde nadovezivanjem
    - `0b1110` - desna polovina iz tačke _1_
    - `0b0101` - rezultat tačke _8_
    - `0b11100101` - rezultat cele runde

## Struktura celog SDES algoritma

1) Plain text se propusti kroz IP
2) Uradi se jedna runda, njen ulazni podatak je izlazni podatak tačke _1_
3) Uradi se druga runda, njen ulazni podatak je izlazni podatak prve runde
4) Leva i desna polovina rezultata druge runde zamene mesta
5) Rezultat tačke _4_ se propusti kroz IP<sup>-1</sup>

### Primer

Svi indeksi počinju od 1

|Identifikator|Vrednost              | 
|-------------|----------------------|
|Plain text   |`0b10111101`          |
|IP           |2, 6, 3, 1, 4, 8, 5, 7|

---

1) Propuštanje kroz IP
    - Prvi bit rezultata je drugi bit plain text-a
    - Drugi bit rezultata je šesti bit plain text-a
    - ...
    - Rezultat je `0b01111110`
2) Prva runda
    - Urađena u gornjem primeru
    - Rezultat je `0b11100101`
3) Druga runda
    - Radi se na isti način kao gornji primer
    - Rezultat je `0b01011001`
4) Zamena mesta leve i desne polovine
    - Leva polovina je rezultata druge runde je `0b0101`
    - Desna polovina je `0b1001`
    - Rezultat je `0b10010101`
5) Propuštanje kroz IP<sup>-1</sup>
    - Prvo moramo da izračunamo IP<sup>-1</sup>
    - IP je _2, 6, 3, 1, 4, 8, 5, 7_
    - Broj _1_ se u IP nalazi na mestu _4_
    - Broj _2_ se u IP nalazi na mestu _1_
    - Broj _3_ se u IP nalazi na mestu _3_
    - Broj _4_ se u IP nalazi na mestu _5_
    - ...
    - IP<sup>-1</sup> je _4, 1, 3, 5, 7, 2, 8, 6_
    - **Na isti način se IP generiše iz IP<sup>-1</sup> u prvoj tački, ukoliko je IP<sup>-1</sup> dato, a IP nije**
    - Prvi bit konačnog rezultata je četvrti bit rezultata tačke _4_
    - ...
    - Konačan rezultat je `0b11000011`
