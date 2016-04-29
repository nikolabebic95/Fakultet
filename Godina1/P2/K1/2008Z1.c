/* Tekst zadatka - http://rti.etf.bg.ac.rs/rti/ir1p2/resenja/SI1P2_0708_K1_resenja.pdf */

#include <stdio.h>

#define MAXNIZA 20
#define MAXNIZB 10

main() {
	float a[MAXNIZA], b[MAXNIZB];
	int na, nb, i, j;

	while (1) {
		printf("Unesite duzinu niza A: ");
		scanf_s("%d", &na);
		if (na <= 0) break;
		printf("Unesite duzinu niza B: ");
		scanf_s("%d", &nb);
		if (nb <= 0) break;
		for (i = 0; i < na; i++) {
			printf("Unesite vrednost %d. clana u nizu A: ", i + 1);
			scanf_s("%f", &a[i]);
		}
		for (i = 0; i < nb;) {
			printf("Unesite vrednost %d. clana u nizu B: ", i + 1);
			scanf_s("%f", &b[i]);
			if (i == 0) i++;
			else if (b[i] > b[i - 1]) i++;
			else printf("Pogresan unos, niz B mora biti rastuci\n");
		}
		for (i = 0; i < na; i++) {
			for (j = 0; j < nb; j++) if (a[i]<b[j]) break;
			printf("Clanu %d u nizu A odgovara vrednost %d\n", i, j-1);
		}
	}
}