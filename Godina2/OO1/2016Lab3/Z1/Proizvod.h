#ifndef _proizvod_h_
#define _proizvod_h_
#include <ostream>

using namespace std;

class Proizvod {
private:
	double cena_;

protected:
	virtual void pisi(ostream &os) const {
		os << cena_;
	}

	double cena() const {
		return cena_;
	}

public:
	explicit Proizvod(double cena): cena_(cena) {}

	virtual double vrednost() const = 0;

	friend ostream &operator<<(ostream &os, const Proizvod &p) {
		p.pisi(os);
		return os;
	}

	virtual ~Proizvod() {}

	virtual Proizvod *kopiraj() const = 0;
};

#endif
