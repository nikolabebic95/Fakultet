#ifndef _artikal_h_
#define _artikal_h_

#include "Roba.h"

class Artikal : public Roba {
private:
	char oznaka_;
	double vrednost_;

protected:
	void pisi(ostream &os) const override {
		os << oznaka_;
	}

public:
	explicit Artikal(char oznaka = '?', double vrednost = 0): oznaka_(oznaka), vrednost_(vrednost) {}

	char oznaka() const {
		return oznaka_;
	}

	double vrednost() const override {
		return vrednost_;
	}

	Artikal *kopiraj() const override {
		return new Artikal(*this);
	}
};

#endif
