#ifndef _merenje_h_
#define _merenje_h_

const long MAXVREME = 86400000;

const double MINTEMPERATURA = -273.15;

#include "Izuzeci.h"
#include <iostream>

using namespace std;

class Merenje {
private:
	long vreme_;
	double temperatura_;

public:
	Merenje(long vreme, double temperatura): vreme_(vreme), temperatura_(temperatura) {
		if (vreme<0 || vreme>MAXVREME) throw LoseVreme();
		if (temperatura < MINTEMPERATURA) throw LosaTemperatura();
	}
	Merenje() = default;

	long getVreme() const { return vreme_; }
	double getTemperatura() const { return temperatura_; }

	friend ostream &operator<<(ostream &izlaz, const Merenje &m) {
		izlaz << "(" << m.vreme_ << "," << m.temperatura_ << ")";
		return izlaz;
	}
};

#endif