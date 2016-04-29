#ifndef _zbirka_h_
#define _zbirka_h_

#include "Izuzeci.h"

template <typename Kljuc, typename Podatak> class Zbirka;

template <typename Kljuc, typename Podatak> class Zbirka<Kljuc*, Podatak*> {
private:
	Kljuc **kljucevi_;
	Podatak **podaci_;
	int brojClanova_ = 0;
	int kapacitet_;

	Zbirka(const Zbirka &z) = delete;
	Zbirka &operator=(const Zbirka &z) = delete;

public:
	Zbirka(int kapacitet = 10) :kapacitet_(kapacitet) {
		kljucevi_ = new Kljuc*[kapacitet];
		podaci_ = new Podatak*[kapacitet];
	}
	~Zbirka();

	void dodaj(Kljuc *k, Podatak *p);
	int getKapacitet() const { return kapacitet_; }
	int getBrojClanova() const { return brojClanova_; }

	bool daLiPostoji(const Kljuc &k) const;

	Podatak &operator[](const Kljuc &k);
	const Podatak &operator[](const Kljuc &k) const { return const_cast<Zbirka&>(*this)[k]; }

	template <typename Kljuc, typename Podatak> friend ostream &operator<<(ostream &izlaz, const Zbirka<Kljuc*, Podatak*> &z);
};

template <typename Kljuc, typename Podatak> void Zbirka<Kljuc*, Podatak*>::dodaj(Kljuc *k, Podatak *p) {
	if (brojClanova_ == kapacitet_) throw Prepunjenje();
	for (int i = 0; i < brojClanova_; i++) if ((*kljucevi_[i++]) == (*k)) throw VecPostoji();
	kljucevi_[brojClanova_] = k;
	podaci_[brojClanova_] = p;
	brojClanova_++;
}

template <typename Kljuc, typename Podatak> Zbirka<Kljuc*, Podatak*>::~Zbirka() {
	for (int i = 0; i < brojClanova_; i++) {
		delete kljucevi_[i];
		delete podaci_[i];
	}
	delete[]kljucevi_;
	delete[]podaci_;
}

template <typename Kljuc, typename Podatak> bool Zbirka<Kljuc*, Podatak*>::daLiPostoji(const Kljuc &k) const {
	for (int i = 0; i < brojClanova_; if ((*kljucevi_[i++]) == k) return true);
	return false;
}

template <typename Kljuc, typename Podatak> Podatak &Zbirka<Kljuc*, Podatak*>::operator[](const Kljuc &k) {
	for (int i = 0; i < brojClanova_; i++) if (k == (*kljucevi_[i])) return *podaci_[i];
	throw NePostoji();
}

template <typename Kljuc, typename Podatak> ostream &operator<<(ostream &izlaz, const Zbirka<Kljuc*, Podatak*> &z) {
	for (int i = 0; i < z.brojClanova_; i++) izlaz << "(" << (*kljucevi_[i]) << "," << (*podaci_[i]) << ")" << endl;
	return izlaz;
}

#endif