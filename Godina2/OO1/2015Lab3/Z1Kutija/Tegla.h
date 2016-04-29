#ifndef _tegla_h_
#define _tegla_h_

#include "Predmet.h"
#include <iostream>

using namespace std;

const double PI = 3.1415926535897; //po standardu nema ni u jednom headeru

class Tegla : public Predmet {
private:
	double poluprecnik_;
	double visina_;

protected:
	void pisi(ostream &izlaz) const override {
		izlaz << "T(";
		Predmet::pisi(izlaz);
		izlaz << ","  << poluprecnik_ << ","  << visina_ << ")";
	}

public:
	Tegla(double poluprecnik, double visina): poluprecnik_(poluprecnik), visina_(visina) {}
	double getZapremina() const override { return poluprecnik_*poluprecnik_*PI*visina_; }
	Tegla *klonirajSe() const override { return new Tegla(*this); }

};

#endif