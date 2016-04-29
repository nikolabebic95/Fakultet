#ifndef _skup_h_
#define _skup_h_

#include "Lista.h"
#include "Kvadar.h"

class Skup : public Lista {
private:

	bool ima(Kvadar *k) const {
		Cvor *t = prvi_;
		while (t != nullptr) {
			if (*t->info_ == *k) return true;
			t = t->sled_;
		}
		return false;
	}

public:
	Lista &operator+=(Kvadar *k) override {
		if (!ima(k)) Lista::operator+=(k);
		else delete[] k;
		return *this;
	}
};

#endif 