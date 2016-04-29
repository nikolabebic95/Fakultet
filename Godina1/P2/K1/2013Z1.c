/* Tekst zadatka - http://rti.etf.bg.ac.rs/rti/ir1p2/resenja/SI1P2_1213_K1_resenja.pdf */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HIGH 255
#define LOW 0

#define MAXSTRING 255

main() {
	unsigned char poruka[MAXSTRING], sifra[MAXSTRING], broj, jedinice, x, i, j, maska, m, temp;
	time_t t;
	while (1) {
		printf("Unesite poruku koju zelite da sifrujete:\n");
		for (i = 0;; i++) {
			x = getchar();
			if (x == '\n') {
				poruka[i] = '\0';
				break;
			}
			poruka[i] = x;
		}
		if (i == 0) break;
		srand((unsigned)time(&t));
		broj = rand()*(HIGH - LOW) / RAND_MAX + LOW;
		for (i = 0, jedinice = 0, x = broj; i < 8; i++) {
			if ((x & 1) == 1) jedinice++;
			x = x >> 1;
		}
		for (i = 0, maska = 0; i < jedinice; i++) {
			for (j = 0, m = 1; j < 7 - i; j++, m *= 2);
			maska += m;
		}
		for (i = 0; poruka[i] != '\0'; i++) {
			x = poruka[i] ^ broj;
			sifra[i] = x;
			temp = x & maska;
			temp = temp >> (8 - jedinice);
			sifra[i] = sifra[i] << jedinice;
			sifra[i] |= temp;
		}
		sifra[i] = '\0';
		printf("Sifrovana poruka je:\n");
		for (i = 0; sifra[i] != '\0'; i++) {
			printf("%x ", sifra[i]);
		}
		printf("\n\n");
	}
}