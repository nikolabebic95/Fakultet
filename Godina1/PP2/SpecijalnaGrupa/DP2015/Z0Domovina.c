/* Tekst zadatka - http://rti.etf.bg.ac.rs/rti/ir1pp2/postavke/2015/SI1PP2_DZ2_2015_Spec_grupa.pdf */

#include <stdio.h>
#include <stdlib.h>

#define MAXMENI 100
#define MAXCENA 1000
#define MAXNARUDZBI 1000


main() {
	while (1) {
		short n, m, i, j, meni[MAXCENA + 1], niz[MAXCENA + 1] = { 0 }, poslindex[MAXCENA + 1], cena, *ispis, brojac, k, l, temp;
		printf("Unesite broj artikala u meniju: ");
		scanf_s("%d", &n);
		if (n <= 0 || n > MAXMENI) exit(0);
		for (i = 0; i < n; i++) {
			printf("Unesite cenu %d. stavke u meniju: ", i + 1);
			scanf_s("%d", &meni[i]);
		}
		niz[0] = 1;
		for (i = 0; i < n; i++) {
			for (j = meni[i]; j <= MAXCENA; j++) {
				temp = niz[j];
				niz[j] += niz[j - meni[i]];
				if (temp == 0 && niz[j] == 1) poslindex[j] = i;
			}
		}
		printf("Unesite broj porudzbina: ");
		scanf_s("%d", &m);
		for (i = 0; i < m; i++) {
			printf("Unesite cenu %d. porudzbine: ", i + 1);
			scanf_s("%d", &cena);
			if (niz[cena] == 0) printf("Impossible\n");
			else if (niz[cena] > 1) printf("Ambiguous\n");
			else {
				ispis = NULL;
				for (j = 0, brojac = cena; brojac > 0; j++) {
					ispis = realloc(ispis, (j + 1)*sizeof(short));
					ispis[j] = poslindex[brojac];
					brojac -= meni[poslindex[brojac]];
				}
				for (k = 0, l = j - 1; k < l; k++, l--) {
					temp = ispis[k];
					ispis[k] = ispis[l];
					ispis[l] = temp;
				}
				printf("Naruceni artikli su: \n");
				for (k = 0; k < j; printf("%d ", ispis[k++] + 1));
				printf("\n");
				free(ispis);
			}
		}
	}
}