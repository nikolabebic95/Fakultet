/* Tekst zadatka - http://rti.etf.bg.ac.rs/rti/ir1p2/resenja/SI1P2_0910_K1_resenja.pdf */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HIGH 100
#define LOW 1
#define MAXBRPOKUSAJA 10

void main() {
	int i, broj, x;
	time_t t;

	srand((unsigned)time(&t));
	while (1) {
		broj = rand()*(HIGH - LOW) / RAND_MAX + LOW;
		for (i = 0; i < MAXBRPOKUSAJA; i++) {
			printf("Ovo vam je %d. pokusaj, unesite broj: ", i + 1);
			scanf_s("%d", &x);
			if (x>broj) printf("Broj koji ste uneli je veci od generisanog\n");
			else if (x < broj) printf("Broj koji ste uneli je manji od generisanog\n");
			else break;
		}
		if (broj == x) printf("Pogodili ste broj %d iz %d. pokusaja\n\n", broj, i + 1);
		else printf("Niste pogodili broj, koji je bio %d\n\n", broj);
	}
}