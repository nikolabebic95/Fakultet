#ifndef _mnogougao_h_
#define _mnogougao_h_

#include "Tacka.h"
#include "Ponderisana.h"
#include <iostream>

using namespace std;


class Mnogougao {
private:
	Tacka **niz_;
	int brojTacaka_;
	int kapacitet_;

	void kopiraj(const Mnogougao &m) {
		kapacitet_ = m.kapacitet_;
		brojTacaka_ = m.brojTacaka_;
		niz_ = new Tacka*[kapacitet_];
		for (int i = 0; i < brojTacaka_; i++) niz_[i] = m.niz_[i]->klonirajSe_();
	}

	void premesti(Mnogougao &m) {
		kapacitet_ = m.kapacitet_;
		brojTacaka_ = m.brojTacaka_;
		niz_ = m.niz_;
		m.niz_ = nullptr;
	}

	void brisi() {
		for (int i = 0; i < brojTacaka_; delete niz_[i++]);
		delete[] niz_;
	}

public:

	explicit Mnogougao(int kapacitet = 3) : kapacitet_(kapacitet), brojTacaka_(0) { niz_ = new Tacka*[kapacitet]; }

	Mnogougao(const Mnogougao &m) { kopiraj(m); }

	Mnogougao &operator=(const Mnogougao &m) {
		if (&m != this) {
			brisi();
			kopiraj(m);
		}
		return *this;
	}

	Mnogougao &operator=(Mnogougao &&m) {
		if (&m != this) {
			brisi();
			premesti(m);
		}
		return *this;
	}

	Mnogougao(Mnogougao &&m) { premesti(m); }

	~Mnogougao() { brisi(); }

	Mnogougao &operator+=(Tacka *t) {
		if (brojTacaka_ == kapacitet_) {
			cerr << "Previse tacaka" << endl;
			exit(-1);
		}
		niz_[brojTacaka_++] = t;
		return *this;
	}

	int getBrojTacaka() const { return brojTacaka_; }

	Tacka *nadjiNajblize() const {
		if (brojTacaka_ == 0) return nullptr;
		double najblize = niz_[0]->udaljenost();
		Tacka *povratna = niz_[0];
		for (int i = 1; i < brojTacaka_; i++) {
			if (double x = niz_[i]->udaljenost() < najblize) {
				najblize = x;
				povratna = niz_[i];
			}
		}
		return povratna;
	}

	friend ostream &operator<<(ostream &izlaz, const Mnogougao &m) {
		izlaz << "[";
		for (int i = 0; i < m.brojTacaka_; i++) {
			izlaz << *m.niz_[i];
			if (i != m.brojTacaka_) izlaz << "|";
		}
		izlaz << "]";
		return izlaz;
	}

};


#endif