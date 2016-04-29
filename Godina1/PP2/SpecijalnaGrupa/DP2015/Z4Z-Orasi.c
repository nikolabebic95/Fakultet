/* Tekst zadatka - http://rti.etf.bg.ac.rs/rti/ir1pp2/postavke/2015/SI1PP2_DZ2_2015_Spec_grupa.pdf */

#include <stdio.h>
#include <stdlib.h>

#define MODUO 8192
#define MAXSLOVA 26

int** pomnozimatrice(int **mat1, int **mat2, int n) {
	int **rez = calloc(n, sizeof(int*)), i, j, k;
	for (i = 0; i < n; i++) rez[i] = calloc(n, sizeof(int));
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			for (k = 0; k < n; k++) {
				rez[i][j] += mat1[i][k] * mat2[k][j];
				rez[i][j] %= MODUO;
			}
		}
	}
	return rez;
}

int** matricanastepen(int **matprva, unsigned long long stepen, int n) {
	int i, j, **matpom;
	unsigned long long  maska = 1, m = stepen;
	int **mat = calloc(n, sizeof(int*));
	for (i = 0; i < n; i++) mat[i] = calloc(n, sizeof(int));
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			mat[i][j] = matprva[i][j];
		}
	}
	while (m) {
		m >>= 1;
		maska <<= 1;
	}
	maska >>= 2;
	while (maska) {
		matpom = pomnozimatrice(mat, mat, n);
		for (i = 0; i < n; i++) free(mat[i]);
		free(mat);
		mat = matpom;
		if (stepen&maska) {
			matpom = pomnozimatrice(mat, matprva, n);
			for (i = 0; i < n; i++) free(mat[i]);
			free(mat);
			mat = matpom;
		}
		maska >>= 1;
	}
	return mat;
}

main() {
	while (1) {
		int brojslova, i, j, *slova, n, *pojavljivanja, *prvavrsta, **mat, **rez;
		unsigned long long brojoraha, stepen;

		printf("Unesite broj slova koje mali Z. ima na raspolaganju: ");
		scanf_s("%d", &brojslova);
		if (brojslova <= 0) break;
		slova = calloc(brojslova, sizeof(int));
		printf("Unesite broj oraha koje mali Z. ima na raspolaganju: ");
		scanf_s("%lld", &brojoraha);
		for (i = 0; i < brojslova; i++) {
			printf("Unesite koliko oraha vredi %d. slovo: ", i + 1);
			scanf_s("%d", &slova[i]);
		}
		n = brojslova + 1;
		pojavljivanja = calloc(n, sizeof(int));
		prvavrsta = calloc(n, sizeof(int));
		for (i = 0; i < brojslova; i++) {
			pojavljivanja[slova[i]]++;
			prvavrsta[slova[i]]++;
		}
		for (i = 1; i < n; i++) {
			for (j = 1; j <= i; j++) {
				prvavrsta[i] += pojavljivanja[j] * prvavrsta[i - j];
				prvavrsta[i] %= MODUO;
			}
		}
		mat = calloc(n, sizeof(int*));
		for (i = 0; i < n; i++) {
			if (i == 0) mat[i] = prvavrsta;
			else mat[i] = calloc(n, sizeof(int));
		}
		for (i = 2; i < n; i++) mat[i][i - 1] = 1;
		for (i = 1; i < n; i++) mat[n - i][brojslova] = pojavljivanja[i];
		if (brojoraha < n) printf("Rec se moze napraviti na %d nacina\n", prvavrsta[brojoraha]);
		else {
			stepen = brojoraha - brojslova + 1;
			rez = matricanastepen(mat, stepen, n);
			printf("Rec se moze napraviti na %d nacina\n", rez[0][brojslova]);
			for (i = 0; i < n; i++) free(rez[i]);
			free(rez);
		}
		for (i = 0; i < n; i++) free(mat[i]);
		free(mat);
		free(pojavljivanja);
		free(slova);
	}
}