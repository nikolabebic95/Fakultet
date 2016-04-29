#ifndef _prodavnica_h_
#define _prodavnica_h_

#include "Izuzeci.h"
#include <iostream>

using namespace std;

template <typename T> class Prodavnica {
private:
	T *niz_;
	int kapacitet_;
	int prvi_;
	int posl_;
	int brojClanova_; //da se ne mucim sa oduzimanjem po modulu :D

	void kopiraj(const Prodavnica &p);
	void premesti(Prodavnica &p) {
		niz_ = p.niz_;
		p.niz_ = nullptr;
		kapacitet_ = p.kapacitet_;
		prvi_ = p.prvi_;
		posl_ = p.posl_;
		brojClanova_ = p.brojClanova_;
	}
	void brisi() { delete[]niz_; niz_ = nullptr; }

public:
	explicit Prodavnica(int kapacitet) : kapacitet_(kapacitet), brojClanova_(0) {
		niz_ = new T[kapacitet];
	}
	~Prodavnica() { brisi(); }

	Prodavnica(const Prodavnica &p) { kopiraj(p); }
	Prodavnica(Prodavnica &&p) { premesti(p); }

	Prodavnica &operator=(const Prodavnica &p) {
		if (this != &p) {
			brisi();
			kopiraj(p);
		}
		return (*this);
	}
	Prodavnica &operator=(Prodavnica &&p) {
		premesti(p);
		return (*this);
	}

	Prodavnica &operator+=(const T &t) {
		if (brojClanova_ == 0) {
			niz_[0] = const_cast<T&>(t);
			prvi_ = posl_ = 0;
			brojClanova_++;
		}
		else if (brojClanova_ == kapacitet_) throw Prepunjenje();
		else {
			posl_++;
			posl_ %= kapacitet_;
			niz_[posl_] = const_cast<T&>(t);
			brojClanova_++;
		}
		return *this;
	}
	T uzmi() {
		if (brojClanova_ == 0) throw NemaNista();
		int indeks = prvi_;
		prvi_++;
		prvi_ %= kapacitet_;
		brojClanova_--;
		return niz_[indeks];
	}
	template <typename T> friend ostream &operator<<(ostream &izlaz, const Prodavnica<T> &p);
};

template <typename T> void Prodavnica<T>::kopiraj(const Prodavnica<T> &p) {
	kapacitet_ = p.kapacitet_;
	brojClanova_ = p.brojClanova_;
	prvi_ = p.prvi_;
	posl_ = p.posl_;
	niz_ = new T[kapacitet_];
	for (int i = 0; i < p.brojClanova_; i++) niz_[(i + p.prvi_) % p.kapacitet_] = p.niz_[(i + p.prvi_) % p.kapacitet_];
}

template <typename T> ostream &operator<<(ostream &izlaz, const Prodavnica<T> &p) {
	izlaz << "[";
	for (int i = 0; i < p.brojClanova_; i++) {
		izlaz << p.niz_[(i + p.prvi_) % p.kapacitet_];
		if (i != p.brojClanova_ - 1) izlaz << ",";
	}
	izlaz << "]";
	return izlaz;
}

#endif