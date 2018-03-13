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
4) Rotacija rezultata tačke 2 ulevo za jedno mesto
    - Početna leva polovina je `0b00001`
    - Početna desna polovina je `0b11000`
    - Rezultat je `0b0001001100`
5) Propuštanje prethodnog rezultata kroz PC2
    - Ključ za drugu rundu je `0b10010010`
