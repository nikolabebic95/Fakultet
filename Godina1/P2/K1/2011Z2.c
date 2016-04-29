/* Tekst zadatka - http://rti.etf.bg.ac.rs/rti/ir1p2/resenja/SI1P2_1011_K1_resenja.pdf */

#include <stdio.h>

main() {
	int i, j, niz[12], flag, s, min, max;
	float prosek, kvartali[4];
	while (1) {
		for (i = 0; i < 12; i++) {
			printf("Unesite prosecnu temperaturu za %d. mesec: ", i + 1);
			scanf_s("%d", &niz[i]);
		}
		for (i = flag = 0; i < 12; i++) {
			if (niz[i]) {
				flag = 1;
				break;
			}
		}
		if (!flag) break;
		for (i = 0; i < 4; i++) {
			for (s = 0, j = 3 * i; j < 3 * i + 3; j++) {
				s = s + niz[j];
			}
			prosek = (float)s / 3;
			kvartali[i] = prosek;
		}
		for (min = max = i = 0; i < 4; i++) {
			printf("Prosecna temperatura u %d. kvartalu je %.2f\n", i, kvartali[i]);
			if (kvartali[i] > max) max = i;
			else if (kvartali[i] < min) min = i;
		}
		printf("Kvartal %d ima najvecu prosecnu temperaturu\n", max + 1);
		printf("Kvartal %d ima najmanju prosecnu temperaturu\n\n", min + 1);
	}
}