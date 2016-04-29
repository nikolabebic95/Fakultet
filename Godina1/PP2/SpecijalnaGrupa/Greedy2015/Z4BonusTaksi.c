/* Tekst zadatka - http://rti.etf.bg.ac.rs/rti/ir1pp2/postavke/2015/SI1PP2_DZ1_2015_Spec_grupa.pdf */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXMAPA 1000000
#define MAXBREL 100000

struct koord {
	int x;
	int y;
};

struct cosak {
	struct koord tacka;
	int udaljenost;
};

main() {
	int x, y, brojhotela, brojraskrsnica, i, indeks, daljina, najdaljina;
	struct koord mesto;
	struct cosak gl, gd, dl, dd;
	gl.udaljenost = gd.udaljenost = dl.udaljenost = dd.udaljenost = 0;

	while (1) {
		printf("Unesite dimenzije grada: ");
		scanf_s("%d %d", &x, &y);
		if ((x <= 0) || (y <= 0) || (x > MAXMAPA) || (y > MAXMAPA)) break;
		printf("Unesite broj hotela: ");
		scanf_s("%d", &brojhotela);
		for (i = 0; i < brojhotela; i++) {
			printf("Unesite koordinate %d. hotela: ", i + 1);
			scanf_s("%d %d", &mesto.x, &mesto.y);
			if ((i==0) || (mesto.x + mesto.y < gl.udaljenost)) {
				gl.tacka = mesto;
				gl.udaljenost = mesto.x + mesto.y;
			}
			if ((i==0) || (mesto.x - mesto.y > gd.udaljenost)) {
				gd.tacka = mesto;
				gd.udaljenost = mesto.x - mesto.y;
			}
			if ((i==0) || (mesto.x - mesto.y < dl.udaljenost)) {
				dl.tacka = mesto;
				dl.udaljenost = mesto.x - mesto.y;
			}
			if ((i==0) || (mesto.x + mesto.y > dd.udaljenost)) {
				dd.tacka = mesto;
				dd.udaljenost = mesto.x + mesto.y;
			}
		}

		printf("Unesite broj raskrsnica: ");
		scanf_s("%d", &brojraskrsnica);
		for (najdaljina = -1, i = 0; i < brojraskrsnica; i++) {
			printf("Unesite koordinate %d. raskrsnice: ", i + 1);
			scanf_s("%d %d", &mesto.x, &mesto.y);
			daljina = 0;
			if (abs(mesto.x - gl.tacka.x) + abs(mesto.y - gl.tacka.y) > daljina) daljina = abs(mesto.x - gl.tacka.x) + abs(mesto.y - gl.tacka.y);
			if (abs(mesto.x - gd.tacka.x) + abs(mesto.y - gd.tacka.y) > daljina) daljina = abs(mesto.x - gd.tacka.x) + abs(mesto.y - gd.tacka.y);
			if (abs(mesto.x - dl.tacka.x) + abs(mesto.y - dl.tacka.y) > daljina) daljina = abs(mesto.x - dl.tacka.x) + abs(mesto.y - dl.tacka.y);
			if (abs(mesto.x - dd.tacka.x) + abs(mesto.y - dd.tacka.y) > daljina) daljina = abs(mesto.x - dd.tacka.x) + abs(mesto.y - dd.tacka.y);
			if ((daljina < najdaljina) || (najdaljina == -1)) {
				najdaljina = daljina;
				indeks = i + 1;
			}
		}
		printf("Minimalna entropija raskrsnice je: ");
		printf("%d\n", najdaljina);
		printf("Indeks raskrsnice sa najmanjom entropijom je: ");
		printf("%d\n", indeks);
	}
}