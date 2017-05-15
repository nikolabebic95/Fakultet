#ifndef _racun_h_
#define _racun_h_

#include "Zbirka.h"
#include "Stavka.h"

class Racun {
private:
	string ime_;
	int datum_;
	Zbirka<Stavka> zbirka_;

	double ukupna_vrednost_ = 0;

public:
	Racun(string ime, int datum, int kapacitet): ime_(ime), datum_(datum), zbirka_(kapacitet) {}

	Racun &operator+=(Stavka *stavka) {
		ukupna_vrednost_ += stavka->velicina();
		zbirka_ += stavka;

		return *this;
	}

	double ukupnaVrednost() const {
		return ukupna_vrednost_;
	}

	friend ostream &operator<<(ostream &os, const Racun &r) {
		os << r.ime_ << " " << r.datum_ << endl;
		os << r.zbirka_;
		os << r.ukupna_vrednost_ << endl;

		return os;
	}
};

#endif
