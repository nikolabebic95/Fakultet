#ifndef _kutija_h_
#define _kutija_h_

#include "Predmet.h"
#include <iostream>
#include <iomanip>

using namespace std;

class Kutija : public Predmet {
private:
	double a_;
	double b_;
	double c_;

protected:
	void pisi(ostream &izlaz) const override {
		izlaz << "K(";
		Predmet::pisi(izlaz);
		izlaz << "," << setprecision(2) << a_ << "," << setprecision(2) << b_ << "," << setprecision(2) << c_ << ")";
	}

public:
	Kutija(double a, double b, double c) : a_(a), b_(b), c_(c) {}
	double getZapremina() const override { return a_*b_*c_; }
	Kutija *klonirajSe() const override { return new Kutija(*this); }

};


#endif