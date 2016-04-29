#ifndef _zbirka_h_
#define _zbirka_h_

#include "MernaTacka.h"

class Zbirka {
private:
	MernaTacka **niz_;
	int kapacitet_;
	int brojClanova_;

	void kopiraj(const Zbirka &m) {
		kapacitet_ = m.kapacitet_;
		brojClanova_ = m.brojClanova_;
		niz_ = new MernaTacka*[kapacitet_];
		for (int i = 0; i < brojClanova_; i++) niz_[i] = m.niz_[i];
	}

	void premesti(Zbirka &m) {
		kapacitet_ = m.kapacitet_;
		brojClanova_ = m.brojClanova_;
		niz_ = m.niz_;
		m.niz_ = nullptr;
	}

	void brisi() {
		delete[] niz_;
	}

public:
	explicit Zbirka(int kapacitet) : kapacitet_(kapacitet), brojClanova_(0) { niz_ = new MernaTacka*[kapacitet]; }

	Zbirka(const Zbirka &z) { kopiraj(z); }

	Zbirka &operator=(const Zbirka &z) {
		if (this != &z) {
			brisi();
			kopiraj(z);
		}
		return *this;
	}

	Zbirka(Zbirka &&z) { premesti(z); }

	Zbirka &operator=(Zbirka &&z) {
		if (this != &z) {
			brisi();
			premesti(z);
		}
		return *this;
	}

	~Zbirka() { brisi(); }

	Zbirka &operator+=(MernaTacka *m) {
		if (brojClanova_ == kapacitet_) {
			cerr << "Prepunjen niz" << endl;
			exit(-1);
		}
		niz_[brojClanova_++] = m;
		return *this;
	}

	int getKapacitet() const { return kapacitet_; }

	int getBrojClanova() const { return brojClanova_; }

	double operator()(int donji, int gornji) const {
		double suma = 0;
		for (int i = 0; i < brojClanova_; suma += (*niz_[i++])(donji, gornji));
		return suma / brojClanova_;
	}

};

#endif