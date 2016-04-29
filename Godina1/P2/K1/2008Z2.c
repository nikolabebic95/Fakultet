/* Tekst zadatka - http://rti.etf.bg.ac.rs/rti/ir1p2/resenja/SI1P2_0708_K1_resenja.pdf */

#include <stdio.h>

main() {
	const int godina[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int dan1, mesec1, dan2, mesec2, razlika;

	while (1) {
		printf("Unesite dan prvog datuma: ");
		scanf_s("%d", &dan1);
		if ((dan1 <= 0) || (dan1 > 31)) break;
		printf("Unesite mesec prvog datuma: ");
		scanf_s("%d", &mesec1);
		if ((mesec1 <= 0) || (mesec1 > 12) || (dan1 > godina[mesec1 - 1])) break;
		printf("Unesite dan drugog datuma: ");
		scanf_s("%d", &dan2);
		if ((dan2 <= 0) || (dan2 > 31)) break;
		printf("Unesite mesec drugog datuma: ");
		scanf_s("%d", &mesec2);
		if ((mesec2 <= 0) || (mesec2 > 12) || (dan2 > godina[mesec2 - 1])) break;
		if (mesec1 == mesec2) {
			razlika = dan1 - dan2;
			if (razlika < 0) razlika = -razlika;
		}
		else if (mesec1 == mesec2 + 1) razlika = godina[mesec2 - 1] - dan2 + dan1 + 1;
		else if (mesec2 == mesec1 + 1) razlika = godina[mesec1 - 1] - dan1 + dan2 + 1;
		else razlika = 11;
		if (razlika > 10) printf("Dani se razlikuju za vise od 10 dana\n\n");
		else printf("Dani se ne razlikuju za vise od 10 dana\n\n");
	}
}