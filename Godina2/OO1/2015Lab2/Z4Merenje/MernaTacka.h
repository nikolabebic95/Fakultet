#ifndef _mernatacka_h_
#define _mernatacka_h_

#include "Tacka.h"
#include "Merenje.h"

class MernaTacka : public Tacka {
private:
	Merenje **niz_;
	int n_;

	void kopiraj(const MernaTacka &m) {
		n_ = m.n_;
		niz_ = new Merenje*[n_];
		for (int i = 0; i < n_; i++) niz_[i] = m.niz_[i];

	}

	void premesti(MernaTacka &m) {
		n_ = m.n_;
		niz_ = m.niz_;
		m.niz_ = nullptr;
		m.n_ = 0;
	}

	void brisi() {
		delete[] niz_;
		n_ = 0;
	}

public:
	MernaTacka(int n, Merenje *niz[], double x = 0, double y = 0, double z = 0) : Tacka(x, y, z), n_(n) {
		niz_ = new Merenje*[n];
		for (int i = 0; i < n; i++) niz_[i] = niz[i];
	}

	MernaTacka(const MernaTacka &m) { kopiraj(m); }

	MernaTacka &operator=(const MernaTacka &m) {
		if (this != &m) {
			brisi();
			kopiraj(m);
		}
		return *this;
	}

	MernaTacka(MernaTacka &&m) { premesti(m); }

	MernaTacka &operator=(MernaTacka &&m) {
		if (this != &m) {
			brisi();
			premesti(m);
		}
		return *this;
	}

	~MernaTacka() { brisi(); }

	Merenje *&operator[](int i) const { return niz_[i]; }

	double operator()(int donji, int gornji) const {
		double suma = 0;
		int brojac = 0;
		for (int i = 0; i < n_; i++) {
			int vreme = niz_[i]->getVreme();
			if (vreme >= donji && vreme <= gornji) {
				suma += niz_[i]->getTemperatura();
				brojac++;
			}
		}
		if (suma != 0) return suma / brojac;
		else return 0;
	}
};

#endif