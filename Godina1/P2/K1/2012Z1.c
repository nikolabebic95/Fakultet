/* Tekst zadatka - http://rti.etf.bg.ac.rs/rti/ir1p2/resenja/SI1P2_1112_K1_resenja.pdf */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

main() {
	double pi, a, b;
	long n, i, unutra, ukupno;
	time_t t;

	while (1) {
		printf("Unesite koliko zelite da generisete brojeva: ");
		scanf_s("%d", &n);
		if (n <= 0) break;
		srand((unsigned)time(&t));
		for (unutra = ukupno = i = 0; i < n; i++) {
			a = (double) rand() / RAND_MAX;
			b = (double) rand() / RAND_MAX;
			if (sqrt(a*a + b*b) <= 1) unutra++;
			ukupno++;
		}
		pi = (double) 4 * unutra / ukupno;
		printf("Vrednost broja pi je %lf\n", pi);
	}
}