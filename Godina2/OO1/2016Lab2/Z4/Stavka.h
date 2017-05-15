#ifndef _stavka_h_
#define _stavka_h_

#include "Predmet.h"
#include <string>

using namespace std;

class Stavka : public Predmet {
private:
	string naziv_;
	double cena_;
	double kolicina_;

public:
	Stavka(string naziv, double cena, double kolicina): naziv_(naziv), cena_(cena), kolicina_(kolicina) {}

	double velicina() const override {
		return cena_ * kolicina_;
	}

	void ispis(ostream &izlaz) const override {
		// Na primer ovako
		cout << naziv_ << " - " << cena_ << " - " << kolicina_;
	}

	Stavka *kopija() const override {
		return new Stavka(*this);
	}
};

#endif
