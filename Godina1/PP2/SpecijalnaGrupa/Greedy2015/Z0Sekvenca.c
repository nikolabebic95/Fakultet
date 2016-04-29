/* Tekst zadatka - http://rti.etf.bg.ac.rs/rti/ir1pp2/postavke/2015/SI1PP2_DZ1_2015_Spec_grupa.pdf */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXREC 8
#define MAXSTRING MAXREC+1
#define MAXBREL 1000000

void main() {
	int n, i, moze, *broj;

	while (1) {
		moze = 1;
		printf("Unesite duzinu niza: ");
		scanf_s("%d", &n);
		if ((n <= 0) || (n > MAXBREL)) break;
		
		broj = calloc(n, sizeof(int));

		unsigned char rec[MAXSTRING], prethodni[MAXSTRING] = { "0" };
		unsigned short j;

		for (i = 0; i < n; i++) {
			printf("Upisite %d. broj: ", i + 1);
			scanf_s("%s", rec, MAXSTRING);
			if (strlen(rec) < strlen(prethodni)) {
				moze = 0;
				break;
			}
			else if (strlen(rec) > strlen(prethodni)) {
				for (j = 0; j < strlen(rec); j++) {
					if (rec[j] == '?') {
						if (j == 0) rec[j] = '1';
						else rec[j] = '0';
					}
				}
				broj[i] = atoi(rec);
			}
			else if (strlen(rec) == strlen(prethodni)) {
				short stek[MAXSTRING], sp = 0;
				for (j = 0; j < strlen(rec); j++) {
					if (rec[j] == '?') {
						rec[j] = prethodni[j];
						stek[sp++] = j;
						if (j == strlen(rec) - 1) {
							short brojac;
							for (brojac = sp - 1; brojac >= 0; brojac--) {
								if (rec[stek[brojac]] == '9') rec[stek[brojac]] = '0';
								else {
									rec[stek[brojac]]++;
									break;
								}
							}
							if (brojac == -1) {
								moze = 0;
								break;
							}
						}
					}
					else if (rec[j] > prethodni[j]) break;
					else if ((rec[j] < prethodni[j]) || ((rec[j] == prethodni[j]) && (j == strlen(rec) - 1))) {
						if (sp == 0) {
							moze = 0;
							break;
						}
						else {
							short brojac;
							for (brojac = sp - 1; brojac >= 0; brojac--) {
								if (rec[stek[brojac]] == '9') rec[stek[brojac]] = '0';
								else {
									rec[stek[brojac]]++;
									break;
								}
							}
							if (brojac == -1) {
								moze = 0;
								break;
							}
							break;
						}
					}
				}
				if (moze) {
					for (; j < strlen(rec); j++) {
						if (rec[j] == '?') rec[j] = '0';
					}
				}
				else break;
				if (broj[i] == 0) broj[i] = atoi(rec);
			}
			if (atoi(rec) == atoi(prethodni)) moze = 0;
			for (j = 0; j < strlen(rec); j++) prethodni[j] = rec[j];
		}
		if (moze) {
			printf("Restauirana sekvenca je:\n");
			for (i = 0; i < n; i++) printf("%d\n", broj[i]);
		}
		else printf("Ne moze se restauirati monotono rastuca sekvenca\n");
		free(broj);
	}
}