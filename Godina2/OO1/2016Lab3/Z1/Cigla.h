#ifndef _cigla_h_
#define _cigla_h_

#include "Proizvod.h"

class Cigla : public Proizvod {
private:
	double a_, b_, c_;

protected:
	void pisi(ostream &os) const override {
		os << "C{" << cena() << "," << a_ << "," << b_ << "," << c_ << "}";
	}

public:
	Cigla(double cena, double a, double b, double c): Proizvod(cena), a_(a), b_(b), c_(c) {}

	double vrednost() const override {
		return cena() * a_ * b_ * c_;
	}

	Cigla *kopiraj() const override {
		return new Cigla(*this);
	}
};

#endif
