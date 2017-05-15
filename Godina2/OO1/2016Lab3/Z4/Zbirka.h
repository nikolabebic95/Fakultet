#ifndef _zbirka_h_
#define _zbirka_h_

#include "Izuzeci.h"

using namespace std;

template <typename T> class Zbirka {
private:
	T **niz_;

	int kapacitet_;
	int korak_;
	int broj_elemenata_ = 0;

	void kopiraj(const Zbirka &z);
	void premesti(Zbirka &z) {
		niz_ = z.niz_;
		kapacitet_ = z.kapacitet_;
		korak_ = z.korak_;
		broj_elemenata_ = z.broj_elemenata_;

		z.niz_ = nullptr;
	}

	void brisi();

public:
	explicit Zbirka(int kapacitet = 10, int korak = 3): kapacitet_(kapacitet), korak_(korak) {
		niz_ = new T*[kapacitet];
	}

	Zbirka &operator+=(T *podatak);

	T *&operator[](int i) {
		if (i < 0 || i > broj_elemenata_) {
			throw IndeksVanOpsega();
		}

		return niz_[i];
	}

	T * const &operator[](int i) const {
		return const_cast<Zbirka &>(*this)[i];
	}

	T *uzmi(int i);

	int brojElemenata() const {
		return broj_elemenata_;
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
	korak_ = z.korak_;
	broj_elemenata_ = z.broj_elemenata_;

	for (int i = 0; i < broj_elemenata_; i++) {
		niz_[i] = z.niz_[i]->kopiraj();
	}
}

template<typename T> void Zbirka<T>::brisi() {
	for (int i = 0; i < broj_elemenata_; i++) {
		delete niz_[i];
	}

	delete[] niz_;
}

template<typename T> Zbirka<T> & Zbirka<T>::operator+=(T *podatak) {
	if (kapacitet_ == broj_elemenata_) {
		T **novi_niz = new T*[kapacitet_ + korak_];
		for (int i = 0; i < broj_elemenata_; i++) {
			novi_niz[i] = niz_[i];
		}

		delete[] niz_;
		niz_ = novi_niz;
		kapacitet_ = kapacitet_ + korak_;
	}

	niz_[broj_elemenata_++] = podatak->kopiraj();

	return *this;
}

template<typename T> T *Zbirka<T>::uzmi(int i) {
	T *povratna = (*this)[i]; // Ovo ce da baci izuzetak ako treba

	for (int j = i; j < broj_elemenata_ - 1; j++) {
		niz_[j] = niz_[j + 1];
	}

	broj_elemenata_--;

	return povratna;
}

#endif
