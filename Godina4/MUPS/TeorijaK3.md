# Adaptivni protokoli

- RWB (Read & Write Broadcast)
    - Prvi upis WU, drugi WI
    - Jedno novo stanje

- EDWP (Efficient Distributed Write Protocol)
    - Invalidacioni prag 3 upisa
    - Tri nova stanja

# Directory protokoli

Katalog predstavlja informacije o tome u čijem kešu se nalazi taj blok. Ima dva bita, jedan koji označava da postoji, i jedan koji označava da li je validan ili je taj procesor upisao nešto u svoj keš (valid i dirty bitovi).

Postoje ravni i hijerarhijski.

## Ravni

Katalog se nalazi uz memoriju, u matičnom čvoru.

Svaki procesor koji u kešu sadrži neki blok zna ko mu je vlasnik, jer su globalne adrese svih blokova jedinstvene - dakle na osnovu adrese bloka se može zaključiti ko mu je vlasnik.

Veličina kataloga zavisi od broja procesora u čijem kešu se možda nalazi blok - O(P), i broja blokova koji postoje na trenutnom procesoru - O(M). Dakle, veličina kataloga je O(MP)

### Akcije protkola:

#### Read miss, dirty bit == 0:
    
1) Procesor koji generiše miss šalje poruku vlasniku kataloga.
2) Vlasnik kataloga šalje blok memorije procesoru koji je generisao miss

#### Read miss, dirty bit == 1:

1) Procesor koji generiše miss šalje poruku vlasniku kataloga.
2) Vlasnik kataloga odgovara da je u taj blok neko upisao, i odgovara na poruku tako što šalje ID procesora koji je upisao (što je u ovom slučaju indeks onog dirty bita koji je 1)
3) Procesor koji generiše miss šalje poruku onom procesoru koji je upisao u blok
4) Procesor koji je upisao u blok odgovara na poruku tako što procesoru koji je generisao miss pošalje blok koji mu treba
5) Procesor koji je upisao u blok šalje poruku vlasniku bloka u kojoj se sadrže novi podaci koje je upisao, kako bi vlasnik mogao da stavi njegov dirty bit na 0.

#### Optimizacija, read miss, dirty bit == 1:

Nema potrebe da se owner ID vraća procesoru koji je generisao RM, nego se zahtev odmah može uputiti procesoru koji sadrži upisane podatke.

1) Procesor koji generiše miss šalje poruku vlasniku kataloga
2) Vlasnik kataloga šalje poruku procesoru koji je upisao u blok
3) Procesor koji je upisao blok u paraleli šalje podatke i onom ko je tražio, i vlasniku bloka, kako bi onaj ko je tražio dobio podatke, a vlasnik mogao da stavi dirty bit na 0

#### Write miss, dirty bit == 0:

1) Procesor koji generiše miss šalje poruku vlasniku kataloga
2) Vlasnik kataloga odgovara na poruku tako što šalje podatke, i informacije o tome koji sve procesori drže taj blok u svojim keševima.
3) Procesor koji generiše miss šalje poruke svim procesorima koji drže blok kako bi ga invalidirali
4) Procesori koji drže blok odgovaraju procesoru koji generiše miss da su primili poruku o invalidaciji (ACK)

#### Izbacivanje bloka zbog algoritma evikcije

Ako je procesor nešto upisivao (dirty bit tog bloka je 1), onda se šalje update vlasniku

Ako procesor nije ništa upisivao (dirty bit tog bloka je 0), onda treba odlučiti da li se šalje update ili ne, ali za tačnost protokola nije bitno


