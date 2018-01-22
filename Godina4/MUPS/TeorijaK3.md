# MUPS Teorija K3

<!-- TOC -->

- [MUPS Teorija K3](#mups-teorija-k3)
- [Adaptivni protokoli](#adaptivni-protokoli)
- [Directory protokoli](#directory-protokoli)
    - [Ravni](#ravni)
        - [Akcije protkola:](#akcije-protkola)
            - [Read miss, dirty bit == 0:](#read-miss-dirty-bit--0)
            - [Read miss, dirty bit == 1:](#read-miss-dirty-bit--1)
            - [Optimizacija, read miss, dirty bit == 1:](#optimizacija-read-miss-dirty-bit--1)
            - [Write miss, dirty bit == 0:](#write-miss-dirty-bit--0)
            - [Izbacivanje bloka zbog algoritma evikcije](#izbacivanje-bloka-zbog-algoritma-evikcije)
        - [Organizacija kataloga](#organizacija-kataloga)
            - [Povećanje bloka](#povećanje-bloka)
            - [Smanjivanje M dimenzije](#smanjivanje-m-dimenzije)
            - [Smanjivanje P dimenzije](#smanjivanje-p-dimenzije)
                - [NB](#nb)
                - [B](#b)
                - [CV](#cv)
                - [SW](#sw)
                - [DP](#dp)
    - [Hijerarhijski protokoli](#hijerarhijski-protokoli)
        - [Inkluzija](#inkluzija)
        - [Dvonivovske hijerarhije](#dvonivovske-hijerarhije)
            - [Prednosti:](#prednosti)
            - [Nedostaci:](#nedostaci)
        - [Hijerarhijski snoopy protokoli](#hijerarhijski-snoopy-protokoli)
            - [Sa centralizovanom globalnom memorijom](#sa-centralizovanom-globalnom-memorijom)
            - [Sa distribuiranim lokalnim memorijama](#sa-distribuiranim-lokalnim-memorijama)
        - [Hijerarhijski directory protokoli](#hijerarhijski-directory-protokoli)
- [Interkonekcione mreže](#interkonekcione-mreže)
    - [Indirektne mreže](#indirektne-mreže)
        - [Magistrala](#magistrala)
        - [Krosbar](#krosbar)
        - [MIN (Multistage interconnection networks)](#min-multistage-interconnection-networks)
    - [Direktne mreže](#direktne-mreže)
        - [Linearni niz](#linearni-niz)
        - [Prsten](#prsten)
        - [Mesh](#mesh)
        - [Torus](#torus)
        - [Hypercube](#hypercube)
            - [CCC](#ccc)
            - [K-arna d-kocka](#k-arna-d-kocka)
        - [Stabla](#stabla)

<!-- /TOC -->

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

Ovakvi katalozi se zovu Dir<sub>i</sub>**X**
- *i* predstavlja broj pointera koji se koriste
- **X** predstavlja strategiju prekoračenja
- Složenost je **O(MlogP)**, jer veličina pointera je reda veličine _logP_, a _i_ je konstanta

Moguće strategije (**X**):
- Dir<sub>_i_</sub>**NB**
- Dir<sub>_i_</sub>**B**
- Dir<sub>_i_</sub>**CV**
- Dir<sub>_i_</sub>**SW**
- Dir<sub>_i_</sub>**DP**

##### NB

Pri prekoračenju pointera, jedan pointer se oslobađa tako što se tom procesoru invalidira blok

##### B

Pri prekoračenju pointera, broadcast bit se postavlja na 1.

Pri upisu, ako je broadcast bit == 1, naredni upis invalidira sve ostale kopije. Ovako se postiže da se ne ograničava broj kopija koje čitaju neki podatak

##### CV

Postoji overflow bit. pri prekoračenju pointera, overflow bit se setuje, i prelazi se na sledeću tehniku:

Ostali biti se raspodele tako da predstavljaju grupe procesora - prvi bit predstavlja prvih K procesora, drugi bit sledećih K...

Bit koji predstavlja neku grupu se setuje ako bilo koji od tih procesora ima kopiju

U slučaju da neki procesor iz grupe sa bitom == 1 pokuša write, cela ta grupa se invalidira (ali ne i svi van te grupe, što je optimizacija u odnosu na prethodnu tehniku)

##### SW

Pri prekoračenju pointera, setuje se overflow bit, i generiše softverski prekid. Taj prekid onda zapamti sve pointere u memoriji.

Pri upisu, ako je overflow bit == 1, ponovo se generiše softverski prekid, i koriste zapamćeni pointeri

Ova tehnika povećava kašnjenje zbog obrade prekida softverski, ali nema nepotrebnih invalidacija

##### DP

Ne postoje pointeri u svakom ulazu, nego samo pokazivač na prvi element liste koja sadrži pointere za taj ulaz. Postoje globalni pointeri koji služe za sve ulaze. Kad nema dovoljno globalnih pointera, neki od njih se invalidira

## Hijerarhijski protokoli

Keš memorije obično nisu ravne, nego postoji više nivoa keševa (na primer, L1, L2 i L3 keš). Ovakve hijerarhije mogu da budu u potpunosti na jednom jezgru, u potpunosti zajedničke za više jezgara, ili da neki nivoi budu privatni za jezgro, a neki deljeni.

Uobičajen slučaj je da su L1 i L2 privatni za jezgro, dok je L3 deljen između jezgara na istom čipu

### Inkluzija

U hijerarhijskim keševima, sadržaj svakog keša nižeg nivoa mora da bude podskup sadržaja keša nivoa iznad njega.

Problem ovde može da nastane kod LRU algoritma zamene - neki blok može biti izbačen iz L2 nivoa, a da ostane u L1 nivou, zbog LRU algoritma zamene.

Ovaj problem se rešava na dva načina:
- L1 ima Write through politiku. Problem se rešava automatski, jer se svaka promena na L1 nivou automatski dešava i na L2 nivou, tako da ako je nešto skoro korišćeno na L1 nivou automatski je skoro korišćeno i na L2 nivou.
- L1 ima Write back politiku. Propagira se korišćenje bloka iz L1 u L2 nivo, tako da nijedan blok neće biti izbačen iz L2 pre nego što je izbačen iz L1. U L2 se za svaki blok uvodi još jedan bit (dirty-invalid), koji označava da je blok menjan u L1 kešu. Pomoću tog bita osiguravamo da kada na magistrali snoop-ujemo da neko traži od nas taj blok, uradimo flush iz L1 u L2, i iz L2 prosledimo dalje, a kada se blok izbaci iz L1 usled zamene, ukoliko je ovaj bit postavljen, flushuje se u L2 nivo.

### Dvonivovske hijerarhije

Čvor je jeden multiprocesor manjeg obima (dakle, čvor je jedan običan računar koji je povezan mrežom sa ostalim čvorovima). Čvor ima svoje nivoe keševa.

Najprostiji primer bi bio da računar ima dva keša, L1 i L2, i da je L1 privatan za jezgro, a L2 zajednički za sva jezgra istog čipa.

Postoje dva protokola, jedan (spoljni) za odnos L2 keša prema memoriji i ostatku mreže, i jedan (unutrašnji) za odnos L1 keša ka L2 kešu.

- Spoljašnji protokol je obično directory-based
- Unutrašnji protokol je obično snoopy-based

U praksi svakako postoje sve 4 kombinacije (snoopy/directory - snoopy/directory)

#### Prednosti:

- Manji potreban prostor za katalog
- Dosta komunikacije se dešava unutar jednog čvora, a ne između čvorova, preko mreže
- Manje udaljenih keš misseva

#### Nedostaci:

- Ako se radi all-to-all komunikacija, ovo je mnogo loše, jer ima mnogo komunikacije između čvorova
- Veće je kašnjenje kod misseva, jer se prvo snoopuje lokalna magistrala, pa tek onda šalje udaljeni zahtev

### Hijerarhijski snoopy protokoli

Postoje dve vrste ovakvih sistema:
- Sa centralizovanom globalnom memorijom
- Sa distribuiranim lokalnim memorijama

#### Sa centralizovanom globalnom memorijom

- L1 keševi su obično SRAM keševi najboljih performansi
- Na magistrali iznad tih keševa (ispod zajedničkog L2) se radi standardni snoopy protokol
- L2 su mnogo veće set-asocijativne keš memorije (DRAM)
- Održava se inkluzija

#### Sa distribuiranim lokalnim memorijama

- Memorija je vezana na L1 keševe, a L2 keš služi za keširanje podataka sa udaljenih memorija
- Ne održava se inkluzija, jer je nepotrebna

### Hijerarhijski directory protokoli

Katalog je organizovan kao stablo. U listovima se nalaze samo procesori i distribuirana memorija. U internim čvorovima se nalaze samo informacije iz kataloga

Svaki čvor je koren stabla za blokove iz svoje memorije. Takođe, on može biti interni čvor ili list za ostale blokove.

Ulaz kataloga govori da li je taj blok keširan u njegovim podsablima, a ako je čvor koren, onda govori i da li su njegovi, lokalni blokovi keširani izvan

Kada se traži informacija o bloku, ide se "uzbrdo" po stablu dok se ne naiđe na čvor koji ume da odgovori

Prednost: Katalozi su manji

Nedostatak: Broj poruka se povećava jer se mora slati više poruka uz i niz stablo

# Interkonekcione mreže

Mreže povezuju procesore, keš memorije, glavne memorije, ulazno-izlazne uređaje...

Za performanse je bitna brzina komunikacije, i energija potrošena za komunikaciju

Glavne projektne odluke:
- Topologija mreže
- Rutiranje unutar mreže
- Baferovanje u mreži

Domeni mreža:
- OCN (On-chip Networks)
- SAN (System/Storage Area Networks)
- LAN (Local Area Networks)
- WAN (Wide Area Networks)

Vrste mreža:
- Indirektne
- Direktne

## Indirektne mreže

Mreže kod kojih su elementi indirektno vezani, preko nekog switch-based medijuma. Kod njih se veze između čvorova uspostavljaju dinamički

### Magistrala

Najprostija indirektna mreža.

Svi elementi su vezani direktno na jednu magistralu, a indirektno međusobno, preko te magistrale

Prednosti:
- Jednostavnost
- Cena je mala
- Održavanje koherencije nije teško

Mane:
- Neskalabilnost
- Samo jedan transfer između dva elementa može da se izvršava u jednom trenutku

### Krosbar

Povezivanje svakog ulaza sa svakim izlazom. Switch na svakom paru ulaz-izlaz. Ukoliko je izlazni port slobodan, može se propustiti ulaz na izlaz

Prednost: Udaljenost svakog dela mreže od svakog drugog je 1 hop

Mana: Neskalabilna, jer je **O(n<sup>2</sup>)** po broju elemenata

### MIN (Multistage interconnection networks)

Ulazi se do izlaza prosleđuju u _logN_ koraka, gde je na svakom koraku svič koji odlučuje na koji od dva izlaza će da prosledi ulaz (slična priča kao sorting networks).

## Direktne mreže

Svaki čvor je direktno vezan sa nekoliko drugih čvorova

Parametri mreža:
- _d_ - Stepen čvora
- _D_ - Prečnik
- Simetrija (u osnosu na svaki čvor)
- Regularnost (ako je stepen svima isti, onda je regularna)
- _B_ - propusni opseg najmanje bisekcije

### Linearni niz

Osobine:
- _d_ = 2
- _D_ = _n_ - 1
- _B_ = 1
- Prosečna udaljenost = ~_n_/3
- Mreža nije simetrična, ali je regularna
- Ponaša se kao magistrala, ali dozvoljava više istovremenih transfera

### Prsten

Osobine:
- _d_ = 2
- _D_ = _n_/2
- _B_ = 2
- Prosečna udaljenost = ~_n_/4
- Simetrična, regularna

### Mesh

Predstavlja 2D matricu elemenata grafa

Osobine:
- _d_ = 4, 3 ili 2
- _D_ = 2(&radic;_n_ - 1)
- _B_ = &radic;_n_
- Pogodna za algoritme koji se dosta oslanjaju na lokalnu komunikaciju sa najbližim susedima
- Mreža nije simetrična, ni regularna

### Torus

Isto kao mesh, samo što su svi redovi i kolone matrice prstenovi

Osobine:
- _d_ = 4
- _D_ = 2(&radic;_n_ - 1)
- _B_ = 2&radic;_n_
- Pogodna za algoritme sa 2D nizovima (matricama)
- Simetrična

### Hypercube

Binarna kocka dimenzije _d_

Binarna kocka je kocka čija svaka ivica ima 2 elementa

Osobine:
- _d_ = 2<sup>_d_</sup>
- _D_ = _d_ - **O(_log n_)**
- _B_ = _n_/2
- Teška za implementaciju za veliko _d_

#### CCC

- U temenima kocke se nalaze prstenovi
- _n_ = _d_*2<sup>_d_</dup>
- _D_ = 2*_d_

#### K-arna d-kocka

Generalizacija hiperkocke tako da ne bude binarna, već na svakoj ivici postoji _k_ elemenata

- _n_ = _k_<sup>_d_</sup>
- Stepen čvora = 2*_d_
- _D_ = _dk_/2

### Stabla

Osobine
- _n_ = 2<sup>k</sup> - 1
- _d_ = 3
- _D_ = 2(_k_ - 1) - **O(_log n_)**
- Problem je usko grlo na višim nivoima
