#ifndef _racun_h_
#define _racun_h_

#include "Predmet.h"
#include "Stavka.h"
#include "Zbirka.h"
#include <string>
#include <iostream>

using namespace std;

class Racun : public Zbirka {
private:
	string ime_;
	int datum_;
public:
	explicit Racun(int kapacitet, string ime, int datum): Zbirka(kapacitet), ime_(ime), datum_(datum) {}

	bool operator+=(Predmet *predmet) override {
		if (typeid(*predmet) == typeid(Stavka)) return Zbirka::operator+=(predmet);
		return false;
	}

	void ispis(ostream &izlaz) const override {
		izlaz << ime_ << endl;
		izlaz << datum_ << endl;
		Zbirka::ispis(izlaz);
		izlaz << zbirVelicina() << endl;
	}
};

#endif
