#include "Imenik.h"

bool Imenik::postoji(Datoteka *d) const {
	for (int i = 0; i < niz_.brojPodataka(); i++) {
		if (niz_[i]->ime() == d->ime()) {
			return true;
		}
	}

	return false;
}

void Imenik::pisi(ostream & os) const {
	for (int i = 0; i < niz_.brojPodataka(); i++) {
		os << *niz_[i] << endl;
	}
}

int Imenik::ukupnaVelicina() const {
	int suma = 0;
	for (int i = 0; i < niz_.brojPodataka(); i++) {
		suma += niz_[i]->velicina();
	}

	return suma;
}
