#ifndef _slozen_h_
#define _slozen_h_

#include <iostream>
#include "Otpornik.h"

using namespace std;

class Slozen : public Otpornik {
private:
	int kapacitet_;

	void kopiraj(const Slozen &s) {
		niz_ = new Otpornik*[s.kapacitet_];
		brojClanova_ = s.brojClanova_;
		kapacitet_ = s.kapacitet_;
		for (int i = 0; i < brojClanova_; i++) niz_[i] = s.niz_[i];
	}

	void premesti(Slozen &s) {
		niz_ = s.niz_;
		s.niz_ = nullptr;
		brojClanova_ = s.brojClanova_;
		kapacitet_ = s.brojClanova_;
	}

	void brisi() {
		delete[] niz_;
		kapacitet_ = 0;
		brojClanova_ = 0;
	}

protected:
	Otpornik **niz_;
	int brojClanova_;

	void pisi(ostream &izlaz) const override {
		izlaz << "(";
		for (int i = 0; i < brojClanova_; i++) {
			izlaz << *niz_[i];
			if (i != brojClanova_ - 1) izlaz << ",";
		}
		izlaz << ")";
	}

public:
	explicit Slozen(int kapacitet = 10) :kapacitet_(kapacitet), brojClanova_(0) { niz_ = new Otpornik*[kapacitet]; }

	Slozen(const Slozen &s) { kopiraj(s); }

	Slozen &operator=(const Slozen &s) {
		if (this != &s) {
			brisi();
			kopiraj(s);
		}
		return *this;
	}

	Slozen(Slozen &&s) { premesti(s); }

	Slozen &operator=(Slozen &&s) {
		if (this != &s) {
			brisi();
			kopiraj(s);
		}
		return *this;
	}

	virtual ~Slozen() { brisi(); }

	double getOtpornost() const override = 0;

	bool operator+=(Otpornik *o) {
		if (brojClanova_ == kapacitet_) return false;
		niz_[brojClanova_++] = o;
		return true;
	}

};

#endif