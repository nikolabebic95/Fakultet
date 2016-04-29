#ifndef _poruka_h_
#define _poruka_h_

#include <iostream>

using namespace std;

class Poruka {
protected:
	virtual void pisi(ostream &izlaz) const = 0;
public:
	friend ostream &operator<<(ostream &izlaz, const Poruka &p) {
		p.pisi(izlaz);
		return izlaz;
	}
	virtual ~Poruka() {}
};

#endif