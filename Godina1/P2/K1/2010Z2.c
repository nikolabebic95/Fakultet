/* Tekst zadatka - http://rti.etf.bg.ac.rs/rti/ir1p2/resenja/SI1P2_0910_K1_resenja.pdf */

#include <stdio.h>

main() {
	int x, y, manji;
	while (1) {
		printf("Unesite prvi broj: ");
		scanf_s("%d", &x);
		printf("Unesite drugi broj: ");
		scanf_s("%d", &y);
		if ((x<=0)||(y<=0)) break;
		if (x < y) manji = x;
		else manji = y;
		for (; manji > 0; manji--) if ((x%manji == 0) && (y%manji == 0)) break;
		x /= manji;
		y /= manji;
		printf("Kada se svedu na uzajamno proste, brojevi su %d i %d\n\n", x, y);
	}
}