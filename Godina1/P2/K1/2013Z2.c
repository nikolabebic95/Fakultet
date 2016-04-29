/* Tekst zadatka - http://rti.etf.bg.ac.rs/rti/ir1p2/resenja/SI1P2_1213_K1_resenja.pdf */

#include <stdio.h>

#define MINBR 0
#define MAXBR 50

#define MAXNIZ 100

void main() {
	int n, niz[MAXNIZ], i, j, min, max, bitseq;
	while (1) {
		printf("Unesite duzinu niza: ");
		scanf_s("%d", &n);
		if ((n <= 0) || (n > MAXNIZ)) break;
		for (i = 0; i < n;) {
			printf("Unesite %d. clan niza: ", i + 1);
			scanf_s("%d", &niz[i]);
			if ((niz[i]<MINBR) || (niz[i]>MAXBR)) printf("Pogresan unos\n");
			else i++;
		}
		for (min = max = i = 0; i < n; i++) {
			if (niz[i] < niz[min]) min = i;
			else if (niz[i] > niz[max]) max = i;
		}
		if (max == min) bitseq = 1;
		if ((niz[max] >= niz[0]) && (niz[max] >= niz[n - 1])) {
			bitseq = 1;
			for (j = max - 1; j > 0; j--) {
				if (niz[j] > niz[j + 1]) {
					bitseq = 0;
					break;
				}
			}
			for (j = max + 1; j < n; j++) {
				if (niz[j] > niz[j - 1]) {
					bitseq = 0;
					break;
				}
			}
		}
		if (((niz[min] <= niz[0]) && (niz[min] <= niz[n - 1]))&&(bitseq==0)) {
			bitseq = 1;
			for (j = min - 1; j > 0; j--) {
				if (niz[j] < niz[j + 1]) {
					bitseq = 0;
					break;
				}
			}
			for (j = min + 1; j < n; j++) {
				if (niz[j] < niz[j - 1]) {
					bitseq = 0;
					break;
				}
			}
		}
		if (bitseq == 1) printf("\nNiz je bitonicka sekvenca\n\n");
		else if (bitseq == 0) printf("\nNiz nije bitonicka sekvenca\n\n");
	}
}