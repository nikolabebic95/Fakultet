/* Tekst zadatka - http://rti.etf.bg.ac.rs/rti/ir1p2/resenja/SI1P2_1011_K1_resenja.pdf */

#include <stdio.h>
#include <stdlib.h>

#define HIGH 10000
#define LOW 10

main() {
	unsigned brojac, broj, f1, f2, temp, seed;
	while (1) {
		brojac = 0;
		printf("Unesite seed za funkciju rand (0 za prekid): ");
		scanf_s("%d", &seed);
		if (seed == 0) break;
		srand(seed);
		while (1) {
			broj = rand()*(HIGH - LOW) / RAND_MAX + LOW;
			for (f1 = f2 = 1; f1 < broj; temp = f1, f1 += f2, f2 = temp);
			brojac++;
			if (broj == f1) break;
		}
		printf("%d je fibonacijev broj, i pogodjen je iz %d. pokusaja\n", broj, brojac);
	}
}