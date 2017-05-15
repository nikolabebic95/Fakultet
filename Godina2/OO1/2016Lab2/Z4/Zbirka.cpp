#include "Zbirka.h"

void Zbirka::kopiraj(const Zbirka & zbirka) {
	kapacitet_ = zbirka.kapacitet_;
	broj_clanova_ = zbirka.broj_clanova_;
	niz_ = new Predmet*[kapacitet_];
	for (auto i = 0; i < broj_clanova_; i++) niz_[i] = zbirka.niz_[i]->kopija();
}

void Zbirka::brisi() {
	for (auto i = 0; i < broj_clanova_; i++) delete niz_[i];
	delete[] niz_;
	niz_ = nullptr;
}

double Zbirka::zbirVelicina() const {
	auto suma = 0.0;
	for (auto i = 0; i < broj_clanova_; i++) suma += niz_[i]->velicina();
	return suma;
}

void Zbirka::ispis(ostream &izlaz) const {
	for (auto i = 0; i < broj_clanova_; i++) izlaz << *niz_[i] << endl;
}
