#ifndef _niz_h_
#define _niz_h_

#include "Izuzeci.h"
#include <iostream>

using namespace std;

template <typename T> class Niz {
private:
	T* niz_;
	int kapacitet_;
	int brojClanova_;

	void kopiraj(const Niz &n);
	void premesti(Niz &n) {
		niz_ = n.niz_;
		kapacitet_ = n.kapacitet_;
		brojClanova_ = n.brojClanova_;
		n.niz_ = nullptr;
	}
	void brisi() {
		delete[]niz_;
		niz_ = nullptr;
	}

public:
	explicit Niz(int kapacitet = 10) : kapacitet_(kapacitet), brojClanova_(0) {
		niz_ = new T[kapacitet];
	}
	~Niz() { brisi(); }

	Niz(const Niz &n) { kopiraj(n); }
	Niz(Niz &&n) { premesti(n); }
	Niz& operator=(const Niz &n) {
		if (this != &n) {
			brisi();
			kopiraj(n);
		}
		return (*this);
	}
	Niz &operator=(Niz &&n) {
		brisi();
		premesti(n);
	}

	Niz &operator+=(T podatak) {
		if (brojClanova_ == kapacitet_) throw Prepunjenje();
		niz_[brojClanova_++] = podatak;
		return (*this);
	}

	T operator[](int mesto) {
		if (mesto < 0 || mesto >= brojClanova_) throw LosIndeks();
		return niz_[mesto];
	}

	const T operator[](int mesto) const { return const_cast<Niz&>(*this)[mesto]; }

	int brojPopunjenih() const { return brojClanova_; }

	template <typename T> friend ostream &operator<<(ostream &izlaz, const Niz &n);

};

template <typename T> void Niz<T>::kopiraj(const Niz &n) {
	kapacitet_ = n.kapacitet_;
	brojClanova_ = n.brojClanova_;
	niz_ = new T[kapacitet_];
	for (int i = 0; i < brojClanova_; i++) niz_[i] = n.niz_[i];
}

template <typename T> ostream &operator<<(ostream &izlaz, const Niz<T> &n) {
	izlaz << "{";
	for (int i = 0; i < n.brojPopunjenih(); i++) {
		izlaz << n[i];
		if (i != n.brojPopunjenih() - 1) izlaz << ",";
	}
	izlaz << "}";
	return izlaz;
}

#endif