#ifndef _ponderisana_h_
#define _ponderisana_h_

#include "Tacka.h"
#include <iostream>

class Ponderisana : public Tacka {
private:

	double q_;

	void pisi(ostream &izlaz) const override {
		Tacka::pisi(izlaz);
		izlaz << "*" << q_;
	}


public:

	Ponderisana(double x = 0, double y = 0, double z = 0, double q = 1) : Tacka(x, y, z), q_(q) {}

	Tacka *klonirajSe_() const override {
		Tacka* nova = new Ponderisana(*this);
		return nova;
	}

	double udaljenost() const override { return Tacka::udaljenost()*q_; }

};


#endif