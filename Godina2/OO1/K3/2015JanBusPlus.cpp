// Tekst zadatka - http://rti.etf.bg.ac.rs/rti/ir2oo1/rokovi/OO1I150123.pdf

#include <iostream>
#include <string>
#include <exception>
#include "conio.h"

using namespace std;

class Datum {
private:
	int mesec_;
	int godina_;

public:
	Datum(int mesec, int godina): mesec_(mesec), godina_(godina) {} //nije explicit da bih mogao da prosledjujem {int, int} kao Datum
	friend bool operator==(const Datum &d1, const Datum &d2) { return (d1.godina_ == d2.godina_) && (d1.mesec_ == d2.mesec_); }
	friend bool operator!=(const Datum &d1, const Datum &d2) { return !(d1 == d2); }
	friend ostream &operator<<(ostream &izlaz, const Datum &d) {
		izlaz << d.mesec_ << "/" << d.godina_;
		return izlaz;
	}

};

class Karta {
private:
	static int brojac_;
	int id_ = brojac_++;

	Karta(const Karta &) = delete;
	Karta &operator=(const Karta &) = delete;

protected:
	virtual void pisi(ostream &izlaz) const { izlaz << id_; }

public:
	Karta() = default;
	virtual bool proveriValjanost(double cena, Datum datum) = 0; //nije const zbog smanjivanja para
	virtual ~Karta() {}
	friend ostream &operator<<(ostream &izlaz, Karta &k) {
		k.pisi(izlaz);
		return izlaz;
	}

};

int Karta::brojac_ = 0;

class Mesecna : public Karta {
private:
	string ime_;
	Datum datum_;

protected:
	void pisi(ostream &izlaz) const override {
		izlaz << ime_ << " (";
		Karta::pisi(izlaz);
		izlaz << ") " << datum_;
	}

public:
	Mesecna(string ime, Datum datum): ime_(ime), datum_(datum) {}
	void produzi(Datum datum) { datum_ = datum; }
	bool proveriValjanost(double cena, Datum datum) override { return datum == datum_; }

};

class Pojedinacna : public Karta {
private:
	double uplacenIznos_;

protected:
	void pisi(ostream &izlaz) const override {
		izlaz << uplacenIznos_ << " (";
		Karta::pisi(izlaz);
		izlaz << ")";
	}

public:
	explicit Pojedinacna(double iznos): uplacenIznos_(iznos) {}
	void dopuni(double iznos) { uplacenIznos_ += iznos; }
	bool proveriValjanost(double cena, Datum datum) override {
		if (cena > uplacenIznos_) return false;
		uplacenIznos_ -= cena;
		return true;
	}

};

class Prepunjenje : public exception {
public:
	const char *what() const override { return "Ne moze se dodati stvar u punu zbirku"; }
};

class NemaNista : public exception {
public:
	const char *what() const override { return "Ne moze se uzeti stvar iz prazne zbirke"; }
};

template <typename T> class Zbirka; //da ne bi moglo ako nije pokazivac
template <typename T> class Zbirka<T*> {
private:
	T** niz_;
	int kapacitet_;
	int brojClanova_; //da se ne mucim sa "sta ako je prvi veci od poslednjeg"
	int prvi_;
	int posl_;

	void kopiraj(const Zbirka &z);
	void premesti(Zbirka &z) {
		niz_ = z.niz_;
		z.niz_ = nullptr;
		kapacitet_ = z.kapacitet_;
		brojClanova_ = z.brojClanova_;
		prvi_ = z.prvi_;
		posl_ = z.posl_;
	}
	void brisi() { delete[]niz_; }

public:
	explicit Zbirka(int kapacitet): kapacitet_(kapacitet), brojClanova_(0) { niz_ = new T*[kapacitet]; }
	Zbirka(const Zbirka &z) { kopiraj(z); }
	Zbirka(Zbirka &&z) { premesti(z); }
	Zbirka &operator=(const Zbirka &z) {
		if (this != &z) {
			brisi();
			kopiraj(z);
		}
		return (*this);
	}
	Zbirka &operator=(Zbirka &&z) {
		premesti(z);
		return (*this);
	}
	~Zbirka() { brisi(); }
	Zbirka &operator<<(T* stvar) {
		if (kapacitet_ == brojClanova_) throw Prepunjenje();
		if (brojClanova_ == 0) {
			niz_[0] = stvar;
			prvi_ = posl_ = 0;
		}
		else {
			posl_ = (posl_ + 1) % kapacitet_;
			niz_[posl_] = stvar;
		}
		++brojClanova_;
		return (*this);
	}
	Zbirka &operator>>(T* &stvar) {
		if (brojClanova_ == 0) throw NemaNista();
		int indeks = prvi_;
		prvi_ = (prvi_ + 1) % kapacitet_;
		--brojClanova_;
		stvar = niz_[indeks];
		return (*this);
	}
	void isprazniZbirku() { brojClanova_ = 0; }
	int getBrojClanova() const { return brojClanova_; }

};

template<typename T> void Zbirka<T*>::kopiraj(const Zbirka &z) {
	niz_ = new T*[z.kapacitet_];
	for (int i = 0; i < z.brojClanova_; i++) { niz_[(i + z.prvi_) % z.kapacitet_] = z.niz_[(i + z.prvi_) % z.kapacitet_]; }
	brojClanova_ = z.brojClanova_;
	kapacitet_ = z.kapacitet_;
	prvi_ = z.prvi_;
	posl_ = z.posl_;
}

class Aparat {
private:
	Zbirka<Karta*> zbirka_;

	Aparat(const Aparat &) = delete;
	Aparat &operator=(const Aparat &) = delete;

public:
	explicit Aparat(int kapacitet = 10): zbirka_(kapacitet) {}
	Aparat &operator+=(Karta *karta) {
		zbirka_<<karta;
		return (*this);
	}
	void proveriValjanostSvih(double cena, Datum datum); //nije const jer cu da vadim i vracam iz zbirke

};

void Aparat::proveriValjanostSvih(double cena, Datum datum) {
	int broj = zbirka_.getBrojClanova();
	for (int i = 0; i < broj; i++) {
		Karta *k = nullptr; //ne da mi kompajler da ga prosledim u operator>> bez da je inicijalizovan
		zbirka_ >> k;
		bool b = k->proveriValjanost(cena, datum); //da bi ispisao tek kad skine pare
		cout << "Karta " << *k << " ";
		if (!b) cout << "nije ";
		cout << "valjana" << endl;
	}
}

int main(void) {
	try {
		Mesecna k1("Nikola", { 1, 2016 });
		Pojedinacna k2(50);
		Pojedinacna k3(100);
		Aparat a(5);
		a += &k1;
		a += &k2;
		a += &k3;
		a.proveriValjanostSvih(70, { 1, 2016 });
	}
	catch (exception &e) { cout << e.what(); }
	_getch();
}

