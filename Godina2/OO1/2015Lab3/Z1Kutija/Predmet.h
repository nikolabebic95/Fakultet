#ifndef _predmet_h_
#define _predmet_h_

#include <iostream>
#include <iomanip>

using namespace std;

class Predmet {
private:
	double tezina_;

protected:
	virtual void pisi(ostream &izlaz) const { izlaz  << tezina_; }

public:
	explicit Predmet(int tezina = 1) : tezina_(tezina) {}
	double getTezina() const { return tezina_*getZapremina(); } //tezina_ je specificna tezina, mnozi se sa zapreminom (ili ja ne znam fiziku)
	void setTezina(double tezina) { tezina_ = tezina; } //jer ce u izvedenim klasama da se zove podrazumevani konstruktor
	virtual double getZapremina() const = 0;
	friend ostream &operator<<(ostream &izlaz, const Predmet &p) {
		p.pisi(izlaz);
		return izlaz;
	}
	virtual Predmet *klonirajSe() const = 0;
	virtual ~Predmet() {}
};

#endif