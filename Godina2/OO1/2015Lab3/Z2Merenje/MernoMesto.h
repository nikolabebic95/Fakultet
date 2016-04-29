#ifndef _mernomesto_h_
#define _mernomesto_h_

#include "Niz.h"
#include "Merenje.h"
#include <iostream>

using namespace std;

class MernoMesto {
private:
	Niz<Merenje> niz_;

public:
	explicit MernoMesto(int kapacitet) : niz_(kapacitet) {}
	MernoMesto() = default;
	MernoMesto &operator+=(Merenje m) { niz_ += m; return(*this); }
	double srednjaVrednost() const;
	friend ostream &operator<<(ostream &izlaz, const MernoMesto &m) {
		izlaz << m.niz_;
		return izlaz;
	}
};

#endif