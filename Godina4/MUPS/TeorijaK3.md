# Adaptivni protokoli

- RWB (Read & Write Broadcast)
    - Prvi upis _WU_, drugi _WI_
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

Veličina kataloga zavisi od broja procesora u čijem kešu se možda nalazi blok - **O(P)**, i broja blokova koji postoje na trenutnom procesoru - **O(M)**. Dakle, veličina kataloga je **O(MP)**

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
4) Procesori koji drže blok odgovaraju procesoru koji generiše miss da su primili poruku o invalidaciji (_ACK_)

#### Izbacivanje bloka zbog algoritma evikcije

Ako je procesor nešto upisivao (dirty bit tog bloka je 1), onda se šalje update vlasniku

Ako procesor nije ništa upisivao (dirty bit tog bloka je 0), onda treba odlučiti da li se šalje update ili ne, ali za tačnost protokola nije bitno

### Organizacija kataloga

Već je rečeno da je veličina kataloga **O(MP)**

- M je veličina memorije (broj blokova)
- P je broj procesora

Ovakav katalog se zove "full map", jer predstavlja potpunu mapu svih procesora i svih blokova.

Katalog će imati puno ulaza kod kojih je valid bit == 0, jer ne koriste svi procesori svaki blok svakog drugog procesora. Zbog toga je moguće optimizovati katalog tako da koristi manje memorije

Moguće optimizacije:

#### Povećanje bloka

Ova optimizacija i dalje ostavlja veličinu kataloga kao O(MP), ali je optimizacija, jer je broj blokova manji, iako je i dalje linearan sa veličinom memorije

#### Smanjivanje M dimenzije

Postojaće veliki broj blokova koje niko od ostalih procesora ne drži, tako da nema poente da se to drži u katalogu sa svim valid bitima == 0. Onda je moguće M dimenziju organizovati kao heš mapu, koja će sadržati samo ulaze koje neko od drugih procesora drži.

#### Smanjivanje P dimenzije

Za većinu blokova neće postojati mnogo procesora koji imaju keširane kopije tih blokova. Obično je taj broj manji ili jednak 5. 

Umesto posebnog bita (tj posebna dva, valid i dirty bita) za svaki blok, svaki ulaz sadrži nekoliko "pokazivača" na procesore koji taj blok drže. Pošto je broj keširanih kopija obično manji ili jednak 5, obično ne treba više od 5 pokazivača.

U ovom slučaju, neophodna je strategija prekoračenja kada nema dovoljno pokazivača za sve procesore

Ovakvi katalozi se zovu Dir<sub>_i_</sub>**X**
- _i_ predstavlja broj pointera koji se koriste
- **X** predstavlja strategiju prekoračenja
- Složenost je **O(MlogP)**, jer veličina pointera je reda veličine _logP_, a _i_ je konstanta

Moguće strategije:

##### Dir<sub>i</sub>**NB**

Pri prekoračenju pointera, jedan pointer se oslobađa tako što se tom procesoru invalidira blok

##### Dir<sub>i</sub>**B**

Pri prekoračenju pointera, broadcast bit se postavlja na 1.

Pri upisu, ako je broadcast bit == 1, naredni upis invalidira sve ostale kopije. Ovako se postiže da se ne ograničava broj kopija koje čitaju neki podatak

##### Dir<sub>i</sub>**CV**

Postoji overflow bit. pri prekoračenju pointera, overflow bit se setuje, i prelazi se na sledeću tehniku:

Ostali biti se raspodele tako da predstavljaju grupe procesora - prvi bit predstavlja prvih K procesora, drugi bit sledećih K...

Bit koji predstavlja neku grupu se setuje ako bilo koji od tih procesora ima kopiju

U slučaju da neki procesor iz grupe sa bitom == 1 pokuša write, cela ta grupa se invalidira (ali ne i svi van te grupe, što je optimizacija u odnosu na prethodnu tehniku)

##### Dir<sub>i</sub>**SW**

Pri prekoračenju pointera, setuje se overflow bit, i generiše softverski prekid. Taj prekid onda zapamti sve pointere u memoriji.

Pri upisu, ako je overflow bit == 1, ponovo se generiše softverski prekid, i koriste zapamćeni pointeri

Ova tehnika povećava kašnjenje zbog obrade prekida softverski, ali nema nepotrebnih invalidacija

##### Dir<sub>i</sub>**DP**

Ne postoje pointeri u svakom ulazu, nego samo pokazivač na prvi element liste koja sadrži pointere za taj ulaz. Postoje globalni pointeri koji služe za sve ulaze. Kad nema dovoljno globalnih pointera, neki od njih se invalidira

