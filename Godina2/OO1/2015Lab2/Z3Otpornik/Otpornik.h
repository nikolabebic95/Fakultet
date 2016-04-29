#ifndef _otpornik_h_
#define _otpornik_h_

#include <iostream>

using namespace std;

class Otpornik {
protected:
	virtual void pisi(ostream &izlaz) const = 0;

public:
	virtual ~Otpornik() {}

	virtual double getOtpornost() const = 0;

	friend ostream &operator<<(ostream &izlaz, const Otpornik &o) {
		o.pisi(izlaz);
		return izlaz;
	}

};

#endif