#ifndef _roba_h_
#define _roba_h_

#include <iostream>

using namespace std;

class Roba {
protected:
	virtual void pisi(ostream &os) const = 0;
public:
	virtual double vrednost() const = 0;

	virtual Roba *kopiraj() const = 0;

	virtual ~Roba() {}

	friend ostream &operator<<(ostream &os, const Roba &r) {
		r.pisi(os);
		return os;
	}
};

#endif
