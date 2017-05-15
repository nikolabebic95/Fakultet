#ifndef _zbirka_h_
#define _zbirka_h_

#include "Predmet.h"

class Zbirka {
private:
	Predmet **niz_;
	int kapacitet_;
	int broj_clanova_ = 0;

	void kopiraj(const Zbirka &zbirka);

	void premesti(Zbirka &zbirka) {
		niz_ = zbirka.niz_;
		zbirka.niz_ = nullptr;
		kapacitet_ = zbirka.kapacitet_;
		broj_clanova_ = zbirka.broj_clanova_;
	}

	void brisi();

public:
	explicit Zbirka(int kapacitet): kapacitet_(kapacitet)  {
		niz_ = new Predmet*[kapacitet_];
	}

	Zbirka(const Zbirka &zbirka) {
		kopiraj(zbirka);
	}

	Zbirka(Zbirka &&zbirka) {
		premesti(zbirka);
	}

	Zbirka &operator=(const Zbirka &zbirka) {
		if (this != &zbirka) {
			brisi();
			kopiraj(zbirka);
		}

		return *this;
	}

	Zbirka &operator=(Zbirka &&zbirka) {
		if (this != &zbirka) {
			brisi();
			premesti(zbirka);
		}

		return *this;
	}

	virtual ~Zbirka() {
		brisi();
	}

	virtual bool operator+=(Predmet *predmet) {
		if (kapacitet_ == broj_clanova_) return false;
		niz_[broj_clanova_++] = predmet->kopija();
		return true;
	}

	double zbirVelicina() const;

	virtual void ispis(ostream &izlaz) const;

	friend ostream &operator<<(ostream &izlaz, const Zbirka &zbirka) {
		zbirka.ispis(izlaz);
		return izlaz;
	}
};

#endif
