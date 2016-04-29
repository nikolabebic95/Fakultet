#ifndef _polica_h_
#define _polica_h_

#include <iostream>
#include "Izuzeci.h"

template <typename T> class Polica; //da bi bacio gresku ako se inicijalizuje nepokazivackim tipom

template <typename T> class Polica<T*> {
private:
	int brojMesta_;
	double nosivost_;
	double trenutnaTezina_;
	T **niz_;

	void kopiraj(const Polica &p);

	void premesti(Polica &p) {
		brojMesta_ = p.brojMesta_;
		nosivost_ = p.nosivost_;
		trenutnaTezina_ = p.trenutnaTezina_;
		niz_ = p.niz_;
		p.niz_ = nullptr;
	}

	void brisi();

	void resetujNiz();

public:
	explicit Polica(int brojMesta = 10, double nosivost = 100) : brojMesta_(brojMesta), nosivost_(nosivost), trenutnaTezina_(0) {
		niz_ = new T*[brojMesta_];
		resetujNiz();
	}
	~Polica() { brisi(); }

	Polica &operator+=(T* stvar);

	T* uzmi(int mesto) {
		if (mesto < 0 || mesto >= brojMesta_) throw LosIndeks();
		T* povratna = niz_[mesto];
		if (niz_[mesto] != nullptr) {
			trenutnaTezina_ -= niz_[mesto]->getTezina();
			niz_[mesto] = nullptr;
		}
		return povratna;
	}

	int brojSlobodnih();

	double tezinaDaSeDoda();

	template <typename T> friend ostream &operator<<(ostream& izlaz, const Polica<T*> &p);

};

//svi koji imaju petlju su van definicije klase, iako sam siguran da VS zna da ih uradi inline, ovaj put ne zelim 99 poena zbog toga :D

template <typename T> void Polica<T*>::kopiraj(const Polica<T*> &p) {
	brojMesta_ = p.brojMesta;
	nosivost_ = p.nosivost;
	trenutnaTezina_ = 0;
	niz_ = new T*[brojMesta_];
	for (int i = 0; i < brojMesta; i++) {
		if (p.niz_[i] == nullptr) niz_[i] == nullptr;
		else niz_[i] = p.niz_[i].klonirajSe();
	}
}

template <typename T> void Polica<T*>::brisi() {
	for (int i = 0; i < brojMesta_; i++) delete niz_[i];
	delete[]niz_;
	niz_ = nullptr;
}

template <typename T> void Polica<T*>::resetujNiz() {
	for (int i = 0; i < brojMesta_; niz_[i++] = nullptr);
}

template <typename T> Polica<T*> &Polica<T*>::operator+=(T* stvar) {
	if (nosivost_ < trenutnaTezina_ + stvar->getTezina()) throw Preopterecenje();
	int i;
	for (i = 0; i < brojMesta_; i++) if (niz_[i] == nullptr) break;
	if (i == brojMesta_) throw NemaMesta();
	trenutnaTezina_ += stvar->getTezina();
	niz_[i] = stvar;
	return (*this);
}

template <typename T> int Polica<T*>::brojSlobodnih() {
	int brojac = 0;
	for (int i = 0; i < brojMesta_; i++) if (niz_[i] != nullptr) brojac++;
	return brojac;
}

template <typename T> double Polica<T*>::tezinaDaSeDoda(){
	if (brojSlobodnih() == 0) return 0;
	double suma = 0;
	for (int i = 0; i < brojMesta_; i++) if (niz_[i] != nullptr) suma += niz_[i]->getTezina();
	return nosivost_ - suma;
}

template <typename T> ostream &operator<<(ostream &izlaz, const Polica<T*> &p) {
	izlaz << "[";
	bool prvi = true;
	for (int i = 0; i < p.brojMesta_; i++) {
		if (p.niz_[i] != nullptr) {
			if (!prvi) izlaz << ",";
			izlaz << *(p.niz_[i]);
			prvi = false;
		}
	}
	izlaz << "]";
	return izlaz;
}

#endif