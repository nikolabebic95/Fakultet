#ifndef _lista_h_
#define _lista_h_

#include "Kvadar.h"
#include <iostream>

using namespace std;

class Lista {
protected:
	struct Cvor {
		Kvadar *info_;
		Cvor *sled_;
		Cvor(Kvadar *info) : info_(info), sled_(nullptr) {}
		~Cvor() { delete info_; }
	};

	Cvor *prvi_;
	Cvor *posl_;

private:

	void brisi() {
		Cvor *t = prvi_;
		while (prvi_ != nullptr) {
			t = prvi_;
			prvi_ = prvi_->sled_;
			delete t;
		}
		posl_ = nullptr;
	}

	void kopiraj(const Lista &l) {
		Cvor *t = l.prvi_;
		while (t != nullptr) *this += t->info_;
	}

	void premesti(Lista &l) {
		prvi_ = l.prvi_;
		posl_ = l.posl_;
		l.prvi_ = nullptr;
		l.posl_ = nullptr;
	}

public:
	Lista() : prvi_(nullptr), posl_(nullptr) {}

	Lista(const Lista &l) { kopiraj(l); }

	Lista &operator=(const Lista &l) {
		if (this != &l) {
			brisi();
			kopiraj(l);
		}
		return *this;
	}

	Lista(Lista &&l) { premesti(l); }

	Lista &operator=(Lista &&l) {
		if (this != &l) {
			brisi();
			premesti(l);
		}
		return *this;
	}

	virtual ~Lista() { brisi(); }

	virtual Lista &operator+=(Kvadar *k) {
		Cvor *novi = new Cvor(k);
		posl_ = (prvi_ == nullptr ? prvi_ : posl_->sled_) = novi;
		return *this;
	}

	friend ostream &operator<<(ostream &izlaz, const Lista &l) {
		Cvor *t = l.prvi_;
		izlaz << "[";
		while (t != nullptr) {
			izlaz << *t->info_;
			if (t->sled_ != nullptr) izlaz << "|";
			t = t->sled_;
		}
		izlaz << "]";
		return izlaz;
	}

};

#endif