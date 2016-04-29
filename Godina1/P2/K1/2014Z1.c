/* Tekst zadatka - http://rti.etf.bg.ac.rs/rti/ir1p2/resenja/SI1P2_1314_K1_resenja.pdf */

#include <stdio.h>

void main() {
	unsigned short int x, y, z, n, i;

	while (1) {
		printf("Unesite broj: ");
		scanf_s("%d", &x);
		n = sizeof(unsigned short int) * 8;
		for (i = 0, z = x, y = 0; i < n; i++) {
			y <<= 1;
			y |= z & 1;
			z >>= 1;
		}
		y = ~y;
		if (x^y) printf("NE\n");
		else printf("DA\n");
	}
}