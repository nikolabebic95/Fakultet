# Uvod u kriptografiju

<!-- TOC -->

- [Uvod u kriptografiju](#uvod-u-kriptografiju)
    - [Cezareva šifra](#cezareva-šifra)
    - [Monoalfabetski algoritam](#monoalfabetski-algoritam)
    - [_Playfair_ algoritam](#_playfair_-algoritam)
    - [_Rail fence_ algoritam](#_rail-fence_-algoritam)
    - [_Row transposition_ algoritam](#_row-transposition_-algoritam)
    - [_Hill cipher_ algoritam](#_hill-cipher_-algoritam)

<!-- /TOC -->

## Cezareva šifra

Svako slovo originalnog teksta se rotira za konstantan pomeraj (U slučaju pomeraja 1, A postaje B, B postaje C, ..., Z postaje A).

Pomeraj za algoritam u originalnom obliku je fiksno 3. U slučaju da je pomeraj _k_, broj _k_ se smatra ključem algoritma.

## Monoalfabetski algoritam

Svako slovo originalnog teksta se menja tačno jednim slovom. Mora da postoji ključ koji mapira svako moguće slovo u slovo, i mapiranje mora da bude 1-1. Mogući ključ: `qwertzuiopasdfghjklyxcvbnm`. Ovo bi značilo da se slovo A menja slovom Q, slovo B slovom W...

## _Playfair_ algoritam

Napravi se matrica veličine _m_\*_n_ - veličina matrice mora da bude bliska broju mogućih slova u alfabetu. Za engleski alfabet sa 26 slova, može se uzeti 5\*5 matrica - u ovom slučaju bi neka dva slova morala da se posmatraju kao jedno slovo. Može se uzeti da se slova _I_ i _J_ posmatraju kao isto slovo (algoritam neće moći da razlikuje ova dva slova kada se poruka dešifruje)

Za _playfair_ algoritam mora postojati ključ. Ključ je jedna reč, i slova te reči se upisuju u matricu, redom po vrstama, ali ne ponavljajući ista slova. Ostatak matrice se popuni ostalim slovima alfabeta, redom. Uzevši da su _I_ i _J_ isto slovo, posmatra se kao da azbuka sadrži samo jedno od ta dva slova, a ne oba.

Ukoliko je ključ reč `vetrobran`, u prvoj vrsti 5\*5 matrice će se naći slova `vetro`, a u prve tri kolone druge vrste slova `ban`. Ovo se dešava da se slovo _r_ ne bi ponovilo dva puta. Ostatak matrice se popuni redom, izbegavajući već iskorišćena slova, i rezultujuća matrica izgleda ovako:

||||||
|---|---|---|---|---|
|V|E|T|R|O|
|B|A|N|C|D|
|F|G|H|I|K|
|L|M|P|Q|S|
|U|W|X|Y|Z|

Originalna poruka se podeli na parove slova redom, ali tako da nijedan par nema dva ista slova. Ovo se postiže tako što se između dva ista slova koja bi narušila pravilnost umetne neko slovo, na primer _x_. Takođe, ako posle ove transformacije poruka ima neparan broj slova, na kraj se doda neko slovo, ponovo na primer _x_.

Na primer, poruka _napadamo u podne ako ne bude vetra_ se deli na _na pa da mo up od ne ak on eb ud ev et ra_

U slučaju da je poruka imala dupla slova, na primer poruka _tweety_, ona bi se podelila u _tw ex et yx_ - x je ubačeno između dva slova _e_, i na kraj, da bi na kraju bio paran broj slova.

Svaki par se šifruje na sledeći način:

1) Ukoliko se oba slova nalaze u istoj vrsti, posmatra se rotacija tih slova u vrsti za jedno mesto desno - na primer _na_ bi se šifrovalo u _cn_.
2) Ukoliko se oba slova nalaze u istoj koloni, posmatra se rotacija tih slova za jedno mesto dole - na primer _bu_ bi se šifrovalo u _fv_
3) U ostalim slučajevima, posmatra se kvadrat čiju dijagonalu čine ta dva slova, i uzima se druga dijagonala. Prvo se uzima donje slovo, pa gornje - na primer _mo_ se šifruje u _se_, a _mx_ se šifruje u _wp_.

## _Rail fence_ algoritam

Do sada su svi algoritmi bili algoritmi zamene. To znači da se neko slovo (ili grupa slova, ili grupa bita) po algoritmu menjala sa nekim drugim slovom. _Rail fence_ algoritam je algoritam transpozicije, što znači da se originalna poruka zadržava, samo se njena slova permutuju.

Način na koji se permutuju slova je sledeći - poruka se napiše _cik-cak_, pa se pročita po vrstama. Broj vrsta predstavlja ključ algoritma.

Primer - poruka _napadamo u podne ako ne bude vetra_, ključ je 3

Cik-cak poruka:

```
n   d   u   n   o   u   e
 a a a o p d e k n b d v t a
  p   m   o   a   e   e   r
```

Šifrovana poruka - _ndunoueaaaopdeknbdvtapmoaeer_

## _Row transposition_ algoritam

Kao i _rail fence_, ovaj algoritam je algoritam transpozicije, što znači da će se u šifrovanoj poruci nalaziti sva originalna slova, permutovana na određen način.

Način na koji se permutuju slova je definisan ključem algoritma.

Ključ predstavlja bilo koju permutaciju brojeva u opsegu `[1,N]`, gde je _N_ neki prirodan broj. Dobro je ako je _N_ reda veličine _√L_, gde je _L_ dužina poruke.

Algoritam radi tako što se poruka napiše tako da u svakom redu ima tačno _N_ slova, osim, možda poslednjeg, u kome sme da ima manje. Onda se poruka čita po kolonama, i to onim redom kako je propisano u ključu.

Primer - poruka _napadamo u podne ako ne bude vetra_, ključ `4 3 1 2 5 6 7`

Poruka po vrstama, sa ključem iznad:

```
4 3 1 2 5 6 7
n a p a d a m
o u p o d n e
a k o n e b u
d e v e t r a
```

U ključu se broj _1_ nalazi na trećem mestu, tako da se treća kolona čita prva. Broj _2_ se nalazi na četvrtom mestu, tako da se četvrta kolona čita druga. Kada ovako pročitamo poruku, dobijemo šifrovan tekst _ppovaoneaukenoadddetanbrmeua_

## _Hill cipher_ algoritam

Kod ovogo algoritma, svi karakteri se kodiraju numeričkim vrednostima, tako što je _a_=0, _b_=1, ..., _z_=25.

Ključ je matrica _m_\*_m_. Bira se _m_ sukcesivnih karaktera iz _plain text_-a, i _m_ šifrovanih karaktera se dobija sledećom formulom:

**_C_ = _P_ * _K_ mod 26**, gde je _C_ šifrovanih _m_ karaktera, _P_ _m_ karaktera iz _plain text_-a, a _K_ ključ. Ovde * predstavlja množenje matrica, a _C_ i _P_ su matrice veličine 1 * _m_.

Ukoliko ne na kraju poruke ne postoji _m_ sukcesivnih karaktera, poruka se dopunjuje nekom vrednošću, na primer _x_.

Dešifrovanje se radi na isti način, samo što se koristi inverzna matrica ključa.

Primer - poruka _pay more money_

Ključ:

```
17 17  5
21 18 21
 2  2 19
```

Prva tri karaktera _plain text_-a su `pay`, i njihova numerička vrednost je `15 0 24`. 

Kada se na to primeni formula, dobije se `17 17 11` - što je šifrovan tekst `rrl`.

Kada se ovako šifruje cela poruka, dobije se _rrlmwbkaspdh_
