#ifndef _paket_h_
#define _paket_h_

#include "Roba.h"
#include "Zbirka.h"

class Paket : public Roba {
private:
	Zbirka<Roba> zbirka_;
	double vrednost_ = 0;

protected:
	void pisi(ostream &os) const override;

public:
	Paket &operator+=(Roba *r) {
		vrednost_ += r->vrednost();
		zbirka_ += r;

		return *this;
	}

	Paket *kopiraj() const override {
		return new Paket(*this);
	}

	double vrednost() const override {
		return vrednost_;
	}
};

#endif
