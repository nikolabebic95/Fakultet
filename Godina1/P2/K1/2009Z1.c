/* Tekst zadatka - http://rti.etf.bg.ac.rs/rti/ir1p2/resenja/SI1P2_0809_K1_resenja.pdf */

#include <stdio.h>

#define GODINA 365
main() {
	const int godine[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int dan, mesec, godina, i;
	unsigned long s;

	while (1) {
		printf("Unesite dan: ");
		scanf_s("%d", &dan);
		if ((dan <= 0) || (dan > 31)) break;
		printf("Unesite mesec: ");
		scanf_s("%d", &mesec);
		if ((mesec <= 0) || (mesec > 12)) break;
		if ((dan > godine[mesec - 1]) && (dan != 29) && (mesec != 2)) break;
		printf("Unesite godinu: ");
		scanf_s("%d", &godina);
		if (godina < 2009) break;
		if ((dan == 29) && (mesec == 2) && (!(((godina % 4 == 0) && (godina % 100 != 0)) || (godina % 1000==0)))) break;
		s = 0;
		for (i = 2009; i < godina; i++, s += GODINA) if (((i % 4 == 0) && (i % 100 != 0)) || (i % 1000==0)) s++;
		for (i = 1; i <= mesec; i++, s += godine[i - 1]);
		for (i = 1; i < dan; s += i++);
		s += 4;
		s %= 7;
		if (s == 0) s = 7;
		printf("%d. %d. %d. je %d. dan u nedelji\n", dan, mesec, godina, s);
	}
}