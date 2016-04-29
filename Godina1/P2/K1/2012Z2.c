/* Tekst zadatka - http://rti.etf.bg.ac.rs/rti/ir1p2/resenja/SI1P2_1112_K1_resenja.pdf */

#include <stdio.h>
#include <math.h>

#define MAXNIZ 100
#define MAX 100
#define MIN 0

main() {
	int n, i, niz[MAXNIZ], pet, sest, sedam, osam, devet, deset, suma;
	float prosek, dev, raz;
	while (1) {
		printf("Unesite broj studenata: ");
		scanf_s("%d", &n);
		if ((n <= 0) || (n > MAXNIZ)) break;
		for (i = 0; i < n;) {
			printf("Unesite broj poena studenta %d: ", i + 1);
			scanf_s("%d", &niz[i]);
			if ((niz[i]<MIN) || (niz[i]>MAX)) printf("Pogresan unos!\n");
			else i++;
		}
		pet = sest = sedam = osam = devet = deset = 0;
		for (suma = i = 0; i < n; i++) {
			if (niz[i] <= 50) pet++;
			else if (niz[i] <= 60) sest++;
			else if (niz[i] <= 70) sedam++;
			else if (niz[i] <= 80) osam++;
			else if (niz[i] <= 90) devet++;
			else deset++;
			suma += niz[i];
		}
		prosek = (float)suma / n;
		for (dev = i = 0; i < n; i++) {
			raz = niz[i] - prosek;
			dev += raz*raz;
		}
		dev = dev / n;
		dev = sqrt(dev);
		printf("Petica ima %d\n", pet);
		printf("Sestica ima %d\n", sest);
		printf("Sedmica ima %d\n", sedam);
		printf("Osmica ima %d\n", osam);
		printf("Devetki ima %d\n", devet);
		printf("Desetki ima %d\n", deset);
		printf("\nProsecna ocena je %.2f\n", prosek);
		printf("Standardna devijacija ocene je %.2f\n\n", dev);
	}
}