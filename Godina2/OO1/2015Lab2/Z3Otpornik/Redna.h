#ifndef _redna_h_
#define _redna_h_

#include "Otpornik.h"
#include "Slozen.h"

class Redna : public Slozen {
private:
	void pisi(ostream &izlaz) const override {
		izlaz << "red";
		Slozen::pisi(izlaz);
	}

public:
	explicit Redna(int kapacitet = 1) :Slozen(kapacitet) {}

	double getOtpornost() const override {
		double suma = 0;
		for (int i = 0; i < brojClanova_; suma += (*niz_[i++]).getOtpornost());
		return suma;
	}

};

#endif