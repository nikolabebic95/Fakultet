#ifndef _element_h_
#define _element_h_

#include <iostream>

using namespace std;

class Element {
protected:
	virtual void pisi(ostream &os) const = 0;
public:
	virtual double velicina() const = 0;

	virtual ~Element() {}

	virtual Element *kopiraj() const = 0;

	friend ostream &operator<<(ostream &os, const Element &e) {
		e.pisi(os);
		return os;
	}
};

#endif
