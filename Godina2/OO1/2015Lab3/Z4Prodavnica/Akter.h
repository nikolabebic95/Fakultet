#ifndef _akter_h_
#define _akter_h_

#include "Prodavnica.h"
#include <iostream>

using namespace std;

template <typename T> class Akter {
private:
	static long long brojac_;
	long long id = brojac_++;

protected:
	virtual void pisi(ostream &izlaz) const { izlaz << id; }
public:
	Akter &operator=(const Akter &) { id = brojac_++; return *this; } //premestajuci ne moram da pisem jer je isto ovo, pozvace se ovo
	virtual ~Akter() {}
	virtual void radnja(Prodavnica<T> &p) const = 0;
	friend ostream &operator<<(ostream &izlaz, const Akter &a) {
		a.pisi(izlaz);
		return izlaz;
	}
};

template <typename T> long long Akter<T>::brojac_ = 0;

#endif