#ifndef _stavka_h_
#define _stavka_h_

#include "Element.h"
#include <string>

using namespace std;

class Stavka : public Element {
private:
	string naziv_;
	double cena_;
	int kolicina_;

protected:
	void pisi(ostream &os) const override {
		os << naziv_ << " " << cena_ << " " << kolicina_ << " " << velicina();
	}

public:
	Stavka(string naziv, double cena, int kolicina): naziv_(naziv), cena_(cena), kolicina_(kolicina) {}

	double velicina() const override {
		return cena_ * kolicina_;
	}

	Stavka *kopiraj() const override {
		return new Stavka(*this);
	}
};

#endif
