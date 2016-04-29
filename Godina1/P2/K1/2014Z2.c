/* Tekst zadatka - http://rti.etf.bg.ac.rs/rti/ir1p2/resenja/SI1P2_1314_K1_resenja.pdf */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

void main() {
	int niz[MAX];
	int i, j, n, temp, pola;
	time_t t;

	while (1) {
		printf("Unesite duzinu niza: ");
		scanf_s("%d", &n);
		if (n <= 0 || n > MAX) break;
		srand((unsigned)time(&t));
		for (i = 0; i < n; i++) {
			niz[i] = rand() * 100 / RAND_MAX + 100;
		}
		for (i = 0, j = n - 1; i < j;) {
			while (i<j) {
				if (niz[i] % 2 == 0) break;
				i++;
			}
			while (i<j) {
				if (niz[j] % 2 == 1) break;
				j--;
			}
			temp = niz[i];
			niz[i] = niz[j];
			niz[j] = temp;
		}
		pola = i;
		for (i = 0; i < pola; i++) {
			for (j = i; j > 0; j--) {
				if (niz[j] > niz[j - 1]) {
					temp = niz[j];
					niz[j] = niz[j - 1];
					niz[j - 1] = temp;
				}
				else break;
			}
		}
		for (i = pola; i < n; i++) {
			for (j = i; j > pola; j--) {
				if (niz[j] < niz[j - 1]) {
					temp = niz[j];
					niz[j] = niz[j - 1];
					niz[j - 1] = temp;
				}
				else break;
			}
		}
		printf("Niz je: ");
		for (i = 0; i < n; i++) {
			printf("%d ", niz[i]);
		}
		printf("\n");
	}
}