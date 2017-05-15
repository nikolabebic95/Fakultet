#ifndef _lista_h_
#define _lista_h_

#include "Izuzeci.h"
#include <iostream>

using namespace std;

template <typename T> class Lista {
private:
	struct Element {
		T *podatak_;
		Element *sled_;

		explicit Element(T *podatak): podatak_(podatak), sled_(nullptr) {}
	};

	Element *prvi_ = nullptr;
	Element *posl_ = nullptr;

	void kopiraj(const Lista &l);
	
	void premesti(Lista &l) {
		prvi_ = l.prvi_;
		posl_ = l.posl_;
		l.prvi_ = l.posl_ = nullptr;
	}

	void brisi();

public:
	Lista() = default;

	Lista &operator+=(T* podatak) {
		Element *novi = new Element(podatak->kopiraj());
		if (prvi_) {
			posl_->sled_ = novi;
		}
		else {
			prvi_ = novi;
		}

		posl_ = novi;

		return *this;
	}

	T* uzmi() {
		if (prvi_ == nullptr) {
			throw PraznaLista();
		}

		Element *stari = prvi_;
		prvi_ = prvi_->sled_;
		if (prvi_ == nullptr) posl_ = nullptr;

		T *povratna = stari->podatak_;
		delete stari;

		return povratna;
	}

	template <typename U> friend ostream &operator<<(ostream &os, const Lista<U> &l);

	Lista(const Lista &l) {
		kopiraj(l);
	}

	Lista(Lista &&l) {
		premesti(l);
	}

	Lista &operator=(const Lista &l) {
		if (this != &l) {
			brisi();
			kopiraj(l);
		}

		return *this;
	}

	Lista &operator=(Lista &&l) {
		if (this != &l) {
			brisi();
			premesti(l);
		}

		return *this;
	}

	~Lista() {
		brisi();
	}
};

#endif

template<typename T> void Lista<T>::kopiraj(const Lista & l) {
	Element tek = l.prvi_;
	while (tek) {
		*this += tek->podatak_;
		tek = tek->sled_;
	}
}

template<typename T> void Lista<T>::brisi() {
	while (prvi_) delete uzmi();
}

template<typename U> ostream & operator<<(ostream & os, const Lista<U> & l) {
	typename Lista<U>::Element *tek = l.prvi_;
	os << "{";
	while (tek) {
		if (tek != l.prvi_) os << ",";
		os << *tek->podatak_;
		tek = tek->sled_;
	}
	os << "}";

	return os;
}
