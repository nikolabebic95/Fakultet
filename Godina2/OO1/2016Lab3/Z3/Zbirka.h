#ifndef _zbirka_h_
#define _zbirka_h_

#include "Izuzeci.h"
#include <iostream>

template <typename T> class Zbirka {
private:
	T **niz_;

	int kapacitet_;
	int broj_elemenata_ = 0;

	void kopiraj(const Zbirka &z);
	void premesti(Zbirka &z) {
		niz_ = z.niz_;
		kapacitet_ = z.kapacitet_;
		broj_elemenata_ = z.broj_elemenata_;
		z.niz_ = nullptr;
	}

	void brisi();

public:
	explicit Zbirka(int kapacitet = 10): kapacitet_(kapacitet) {
		niz_ = new T*[kapacitet];
	}

	Zbirka &operator+=(T *podatak) {
		if (broj_elemenata_ == kapacitet_) {
			throw PunaZbirka();
		}

		niz_[broj_elemenata_++] = podatak->kopiraj();

		return *this;
	}

	T *&operator[](int i) {
		if (i < 0 || i > broj_elemenata_) {
			throw NePostojiElement();
		}

		return niz_[i];
	}

	T * const &operator[](int i) const {
		return const_cast<Zbirka &>(*this)[i];
	}

	int brojElemenata() const {
		return broj_elemenata_;
	}

	friend ostream &operator<<(ostream &os, const Zbirka &z) {
		for (int i = 0; i < z.broj_elemenata_; i++) {
			os << *z.niz_[i] << endl;
		}

		return os;
	}

	Zbirka(const Zbirka &z) {
		kopiraj(z);
	}

	Zbirka(Zbirka &&z) {
		premesti(z);
	}

	Zbirka &operator=(const Zbirka &z) {
		if (this != &z) {
			brisi();
			kopiraj(z);
		}

		return *this;
	}

	Zbirka &operator=(Zbirka &&z) {
		if (this != &z) {
			brisi();
			premesti(z);
		}

		return *this;
	}

	~Zbirka() {
		brisi();
	}
};

template<typename T> void Zbirka<T>::kopiraj(const Zbirka & z) {
	niz_ = new T*[z.kapacitet_];
	kapacitet_ = z.kapacitet_;
	broj_elemenata_ = z.broj_elemenata_;

	for (int i = 0; i < broj_elemenata_; i++) {
		niz_[i] = z.niz_[i]->kopiraj();
	}
}

template<typename T> void Zbirka<T>::brisi() {
	for (int i = 0; i < broj_elemenata_; i++) {
		delete niz_[i];
	}

	delete [] niz_;
}

#endif
