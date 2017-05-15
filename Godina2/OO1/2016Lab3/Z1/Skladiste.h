#ifndef _skladiste_h_
#define _skladiste_h_

#include "Lista.h"
#include "Proizvod.h"

class Skladiste {
private:
	Lista<Proizvod> lista_;

	double trenutna_vrednost_ = 0;
	double ukupna_vrednost_ = 0;

	Skladiste(const Skladiste &) = delete;
	void operator=(const Skladiste &) = delete;
public:
	Skladiste() = default;

	Skladiste &operator+=(Proizvod *p) {
		lista_ += p;
		trenutna_vrednost_ += p->vrednost();
		ukupna_vrednost_ += p->vrednost();
		return *this;
	}

	Proizvod *uzmi() {
		Proizvod *povratna = lista_.uzmi();
		trenutna_vrednost_ -= povratna->vrednost();
		return povratna;
	}

	double trenutnaVrednost() const {
		return trenutna_vrednost_;
	}

	double ukupnaVrednost() const {
		return ukupna_vrednost_;
	}

	void pocniPosmatranje() {
		ukupna_vrednost_ = 0;
	}

	friend ostream &operator<<(ostream &os, const Skladiste &s) {
		os << s.lista_;
		return os;
	}
};

#endif
