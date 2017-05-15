#ifndef _predmet_h_
#define _predmet_h_

#include <iostream>

using namespace std;

class Predmet {
public:
	virtual double velicina() const = 0;

	virtual void ispis(ostream &izlaz) const = 0;

	friend ostream &operator<<(ostream &izlaz, const Predmet &predmet) {
		predmet.ispis(izlaz);
		return izlaz;
	}

	virtual Predmet *kopija() const = 0;

	virtual ~Predmet() {}
};

#endif
