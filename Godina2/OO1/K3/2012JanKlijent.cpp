// Tekst zadatka - http://home.etf.rs/~kraus/nastava/oop1/ispiti/isp_2012_01_19.html

#include <iostream>
#include <exception>
#include <conio.h>
#include <cstdlib>
#include <ctime>

using namespace std;

class PrazanRed : public exception {
public:
	const char *what() const override { return "Ne moze se uzeti iz praznog reda"; }
};

class Osoba {
private:
	static int brojac_;
	int identifikator_ = brojac_++;
protected:
	virtual void pisi(ostream &izlaz) const { izlaz << vrsta() << " " << identifikator_; }
public:
	Osoba &operator=(const Osoba &o) { identifikator_ = brojac_++; } //premestajuci poziva ovo
	virtual char vrsta() const = 0;
	friend ostream &operator<<(ostream &izlaz, const Osoba &o) {
		o.pisi(izlaz);
		return izlaz;
	}
	virtual Osoba *klonirajSe() const = 0;
	virtual ~Osoba() {}
};
int Osoba::brojac_ = 0;

class Klijent : public Osoba {
private:
	char usluga_;

	void generisiUslugu() {
		int i = (int)((rand() / ((double)(RAND_MAX + 1))) * 3);
		if (i == 0) usluga_ = 'a';
		else if (i == 1) usluga_ = 'b';
		else usluga_ = 'c';
	}
protected:
	void pisi(ostream &izlaz) const {
		Osoba::pisi(izlaz);
		izlaz << " (" << usluga_ << ")";
	}
public:
	Klijent() { generisiUslugu(); }
	char vrsta() const override { return 'K'; }
	char usluga() const { return usluga_; }
	Klijent *klonirajSe() const { return new Klijent(*this); }
};

template <typename T> class Red {
private:
	struct Clan {
		T *info_;
		Clan *sled_;
		explicit Clan(T *info): info_(info), sled_(nullptr) {}
	};

	Clan *prvi_;
	Clan *posl_;

	void kopiraj(const Red &r);
	void premesti(Red &r) {
		prvi_ = r.prvi_;
		posl_ = r.posl_;
		r.prvi_ = nullptr;
		r.posl_ = nullptr;
	}
	void brisi();

public:
	Red(): prvi_(nullptr), posl_(nullptr) {}
	Red(const Red &r) { kopiraj(r); }
	Red(Red &&r) { premesti(r); }
	Red &operator=(const Red &r) {
		if (this != &r) {
			brisi();
			kopiraj(r);
		}
		return *this;
	}
	Red &operator=(Red &&r) {
		brisi();
		premesti(r);
		return *this;
	}
	~Red() { brisi(); }
	Red &operator+=(T *info) {
		posl_ = ((prvi_ == nullptr) ? prvi_ : posl_->sled_) = new Clan(info);
		return *this;
	}
	T *uzmi() {
		if (prvi_ == nullptr) throw PrazanRed();
		Clan *pom = prvi_;
		T *povratna = prvi_->info_;
		prvi_ = prvi_->sled_;
		if (prvi_ == nullptr) posl_ = nullptr;
		delete pom;
		return povratna;
	}
	bool prazan() const { return prvi_ == nullptr; }
};

template<typename T> void Red<T>::kopiraj(const Red & r) {
	prvi_ = nullptr;
	posl_ = nullptr;
	tek = r.prvi_;
	while (tek != nullptr) (*this) += tek->info_->klonirajSe();
}

template<typename T> void Red<T>::brisi() {
	while (!prazan()) delete uzmi();
}

class Radnik : public Osoba {
protected:
	Klijent *klijent_ = nullptr;
	void pisi(ostream &izlaz) const override {
		Osoba::pisi(izlaz);
		if (klijent_ != nullptr) izlaz << " " << *klijent_;
		izlaz << endl;
	}
public:
	virtual void operator()(Red<Klijent> &ulazni, Red<Klijent> &a, Red<Klijent> &b, Red<Klijent> &c) = 0 { cout << *this; }
};

class Portir : public Radnik {
public:
	char vrsta() const override { return 'P'; }
	Portir *klonirajSe() const override { return new Portir(*this); }
	void operator()(Red<Klijent> &ulazni, Red<Klijent> &a, Red<Klijent> &b, Red<Klijent> &c) override {	
		klijent_ = new Klijent;
		ulazni += klijent_;
		Radnik::operator()(ulazni, a, b, c);
	}
};

class Razvodnik : public Radnik {
public:
	char vrsta() const override { return 'R'; }
	Razvodnik *klonirajSe() const override { return new Razvodnik(*this); }
	void operator()(Red<Klijent> &ulazni, Red<Klijent> &a, Red<Klijent> &b, Red<Klijent> &c) override {
		if (ulazni.prazan()) klijent_ = nullptr;
		else {
			klijent_ = ulazni.uzmi();
			if (klijent_->usluga() == 'a') a += klijent_;
			else if (klijent_->usluga() == 'b') b += klijent_;
			else c += klijent_;
		}
		Radnik::operator()(ulazni, a, b, c);
	}
};

class Sluzbenik : public Radnik {
private:
	char red_;
public:
	explicit Sluzbenik(char red): red_(red) {}
	char vrsta() const override { return 'S'; }
	Sluzbenik *klonirajSe() const override { return new Sluzbenik(*this); }
	void operator()(Red<Klijent> &ulazni, Red<Klijent> &a, Red<Klijent> &b, Red<Klijent> &c) override {
		Red<Klijent> *njegov;
		if (red_ == 'a') njegov = &a;
		else if (red_ == 'b') njegov = &b;
		else njegov = &c;
		if (njegov->prazan()) klijent_ = nullptr;
		else klijent_ = njegov->uzmi();
		Radnik::operator()(ulazni, a, b, c);
		delete klijent_;
		klijent_ = nullptr;
	}
};

class Sluzba {
private:
	Red<Klijent> ulazni_;
	Red<Klijent> a_;
	Red<Klijent> b_;
	Red<Klijent> c_;
	Portir portir_;
	Razvodnik razvodnik_;
	Sluzbenik sA_ = Sluzbenik('a');
	Sluzbenik sB_ = Sluzbenik('b');
	Sluzbenik sC_ = Sluzbenik('c');
public:
	void radnja() {
		int i = (int)((rand() / ((double)(RAND_MAX + 1))) * 5);
		if (i == 0) portir_(ulazni_, a_, b_, c_);
		else if (i == 1) razvodnik_(ulazni_, a_, b_, c_);
		else if (i == 2) sA_(ulazni_, a_, b_, c_);
		else if (i == 3) sB_(ulazni_, a_, b_, c_);
		else sC_(ulazni_, a_, b_, c_);
	}
};

int main(void) {
	time_t t;
	srand(unsigned(time(&t))); //u c++ sigurno ima bolja fora ali ja nemam pojma
	Sluzba s;
	for (int i = 0; i < 100; i++) s.radnja();
	_getch();
}

