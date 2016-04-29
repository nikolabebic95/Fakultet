#ifndef _prost_h_
#define _prost_h_

#include "Otpornik.h"
#include <iostream>

class Prost : public Otpornik {
private:
	double r_;

	void pisi(ostream &izlaz) const override {
		izlaz << r_;
	}

public:
	Prost(double r = 1) : Otpornik(), r_(r) {}

	double getOtpornost() const { return r_; }
};

#endif