#; Na x86 asembleru napisati deo programa koji u sekciji za podatke alocira prostor za niz od 100 elemenata velicine 4B.
#; Alocirani prostor treba popuniti ponavljanjem vrednosti 1, 2, 3, 4, 5, 6 i 7. Pocetak alociranog prostora oznaciti
#; labelom ARRAY_BEGIN, dok prvu adresu posle kraja niza treba oznaciti labelom ARRAY_END. Sadrzaj fajla treba da bude
#; minimalne moguce velicine (ne sme sadrzati druge sekcije osim sekcije za podatke).

.intel_syntax noprefix
.arch i386

.data

.globl ARRAY_BEGIN
ARRAY_BEGIN:
                .rept 14
                .long 1, 2, 3, 4, 5, 6, 7
                .endr
                .long 1, 2
.globl ARRAY_END
ARRAY_END:
