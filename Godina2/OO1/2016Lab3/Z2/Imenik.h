#ifndef _imenik_h_
#define _imenik_h_

#include "Datoteka.h"
#include "Niz.h"

class Imenik : public Datoteka {
private:
	Niz<Datoteka > niz_;

	bool postoji(Datoteka *d) const;

protected:
	void pisi(ostream &os) const override;

public:
	explicit Imenik(string ime) : Datoteka(ime, 100) {}

	Imenik &operator+=(Datoteka *d) {
		if (postoji(d)) {
			throw PostojiDatoteka();
		}

		d->roditelj(this);
		niz_ += d;
		povecajVelicinu(10);
		return *this;
	}

	int brojDatoteka() const {
		return niz_.brojPodataka();
	}

	Datoteka *&operator[](int i) {
		return niz_[i];
	}

	Datoteka * const &operator[](int i) const {
		return const_cast<Imenik &>(*this)[i];
	}

	int ukupnaVelicina() const;

	Imenik *kopiraj() const override {
		return new Imenik(*this);
	}
};

#endif
