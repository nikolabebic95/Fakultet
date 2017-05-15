#ifndef _niz_h_
#define _niz_h_
#include "Izuzeci.h"

template <typename T> class Niz {
private:
	static const int PODRAZUMEVANI_KAPACITET = 5;

	T **niz_ = new T*[PODRAZUMEVANI_KAPACITET];
	int kapacitet_ = PODRAZUMEVANI_KAPACITET;
	int broj_elemenata_ = 0;

	void kopiraj(const Niz &n);
	void premesti(Niz &n) {
		niz_ = n.niz_;
		n.niz_ = nullptr;
	}
	void brisi();

public:
	Niz() = default;

	Niz &operator+=(T *podatak) {
		if (broj_elemenata_ == kapacitet_) {
			T **novi_niz = new T*[kapacitet_ + PODRAZUMEVANI_KAPACITET];
			for (int i = 0; i < broj_elemenata_; i++) {
				novi_niz[i] = niz_[i]->kopiraj();
			}

			kapacitet_ = kapacitet_ + PODRAZUMEVANI_KAPACITET;
		}

		niz_[broj_elemenata_++] = podatak->kopiraj();

		return *this;
	}

	T *&operator[](int i) {
		if (i < 0 || i > broj_elemenata_) {
			throw IndeksVanOpsega();
		}

		return niz_[i];
	}

	T * const &operator[](int i) const {
		return const_cast<Niz &>(*this)[i];
	}

	int brojPodataka() const {
		return broj_elemenata_;
	}

	template <typename U> friend ostream &operator<<(ostream & os, const Niz &niz);

	Niz(const Niz &n) {
		kopiraj(n);
	}

	Niz(Niz &&n) {
		premesti(n);
	}

	Niz &operator=(const Niz &n) {
		if (this != &n) {
			brisi();
			kopiraj(n);
		}

		return *this;
	}

	Niz &operator=(Niz &&n) {
		if (this != &n) {
			brisi();
			premesti(n);
		}

		return *this;
	}

	~Niz() {
		brisi();
	}
};

#endif

template<typename T> void Niz<T>::kopiraj(const Niz & n) {
	niz_ = new T*[n.kapacitet_];
	for (int i = 0; i < n.brojPodataka(); i++) {
		niz_[i] = n.niz_[i]->kopiraj();
	}

	broj_elemenata_ = n.broj_elemenata_;
}

template<typename T> void Niz<T>::brisi() {
	for (int i = 0; i < broj_elemenata_; i++) {
		delete niz_[i];
	}

	delete niz_;
	niz_ = nullptr;
}

template<typename U> ostream & operator<<(ostream & os, const Niz<U>& niz) {
	for (int i = 0; i < niz.broj_elemenata_; i++) {
		os << *niz.niz_[i] << endl;
	}

	return os;
}
