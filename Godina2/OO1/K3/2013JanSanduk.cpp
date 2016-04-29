// Tekst zadatka - http://home.etf.rs/~kraus/nastava/oop1/ispiti/isp_2013_01_17.html

#include <iostream>
#include <exception>
#include <conio.h>

using namespace std;

const double PI = 3.1415926535897;

class Stvar {
protected:
	virtual bool uporedi(const Stvar &s) const = 0;
public:
	friend bool operator==(const Stvar &s1, const Stvar &s2) { return s1.uporedi(s2); }
	virtual ~Stvar() {}
};

class Proizvod : public Stvar {
private:
	static int brojac_;
	int identifikator_ = brojac_++;
protected:
	virtual void pisi(ostream &izlaz) const { izlaz << oznakaVrste() << " " << identifikator_; }
	virtual bool uporedi(const Stvar &s) const override { return oznakaVrste() == (dynamic_cast<const Proizvod&>(s)).oznakaVrste(); }
public:
	virtual char oznakaVrste() const = 0;
	virtual double zapremina() const = 0;
	virtual Proizvod *klonirajSe() const = 0;
	friend ostream &operator<<(ostream &izlaz, const Proizvod &p) {
		p.pisi(izlaz);
		return izlaz;
	}
	virtual ~Proizvod() {}
};
int Proizvod::brojac_ = 0;

class Sanduk : public Proizvod {
private:
	double a_;
	double b_;
	double c_;
protected:
	void pisi(ostream &izlaz) const override {
		Proizvod::pisi(izlaz);
		izlaz << " " << a_ << " " << b_ << " " << c_;
	}
	bool uporedi(const Stvar &s) const override {
		bool povratna = Proizvod::uporedi(s);
		if (povratna) {
			const Sanduk &sanduk = dynamic_cast<const Sanduk &>(s);
			return a_ == sanduk.a_ && b_ == sanduk.b_ && c_ == sanduk.c_;
		} //da dynamic cast nikad ne bi bacio exception, iako je ceo koncept los ali takav je zadatak
		return false;
	}
public:
	Sanduk(double a, double b, double c): a_(a), b_(b), c_(c) {}
	char oznakaVrste() const override { return 'S'; }
	double zapremina() const override { return a_*b_*c_; }
	Sanduk *klonirajSe() const override { return new Sanduk(*this); }
};

class Bure : public Proizvod {
private:
	double osnova_;
	double visina_;
protected:
	void pisi(ostream &izlaz) const {
		Proizvod::pisi(izlaz);
		izlaz << " " << osnova_ << " " << visina_;
	}
	bool uporedi(const Stvar &s) const override {
		bool povratna = Proizvod::uporedi(s);
		if (povratna) {
			const Bure &bure = dynamic_cast<const Bure &>(s);
			return osnova_ == bure.osnova_ && visina_ == bure.visina_;
		} //da dynamic cast nikad ne bi bacio exception, iako je ceo koncept los ali takav je zadatak
		return false;
	}
public:
	Bure(double osnova, double visina): osnova_(osnova), visina_(visina) {}
	char oznakaVrste() const override { return 'B'; }
	double zapremina() const override { return osnova_*PI*visina_; }
	Bure *klonirajSe() const override { return new Bure(*this); }
};

class Prepunjenje : exception {
public:
	const char *what() const override { return "Ne moze se dodati stvar u punu zbirku"; }
};

class NemaTaj : exception {
public:
	const char *what() const override { return "U zbirci ne postoji taj podatak"; }
};

template <typename T> class Zbirka; //mora pokazivaci
template <typename T> class Zbirka<T*> {
protected: //lose resenje ali ne bih se ni na ispitu setio odmah da treba
	T **niz_;
	int kapacitet_;

	void kopiraj(const Zbirka &z);
	void premesti(Zbirka &z) {
		niz_ = z.niz_;
		z.niz_ = nullptr;
		kapacitet_ = z.kapacitet_;
	}
	void brisi();
	void resetuj();

public:
	explicit Zbirka(int kapacitet) : kapacitet_(kapacitet) {
		niz_ = new T*[kapacitet];
		resetuj();
	}
	Zbirka(const Zbirka &z) { kopiraj(z); }
	Zbirka(Zbirka &&z) { premesti(z); }
	Zbirka &operator=(const Zbirka &z) {
		if (this != &z) {
			brisi();
			kopiraj();
		}
		return (*this);
	}
	Zbirka &operator=(Zbirka &&z) {
		brisi();
		premesti();
		return (*this);
	}
	virtual ~Zbirka() { brisi(); }
	virtual Zbirka &operator+=(T* stvar);
	T *operator-=(const T &stvar);
	int brojSlobodnihMesta() const;
	template <typename T> friend ostream &operator<<(ostream &izlaz, const Zbirka<T*> &z);
};

template<typename T> void Zbirka<T*>::kopiraj(const Zbirka &z) {
	kapacitet_ = z.kapacitet_;
	niz_ = new T*[kapacitet_];
	resetuj();
	for (int i = 0; i < kapacitet_; i++) if (z.niz_[i] != nullptr) niz_[i] = z.niz_[i]->klonirajSe();
}

template<typename T> void Zbirka<T*>::brisi() {
	T *trenutni = nullptr;
	for (int i = 0; i < kapacitet_; delete niz_[i++]);
	delete[]niz_;
}

template<typename T> void Zbirka<T*>::resetuj() {
	for (int i = 0; i < kapacitet_; niz_[i++] = nullptr);
}

template<typename T> Zbirka<T*> & Zbirka<T*>::operator+=(T * stvar) {
	for (int i = 0; i < kapacitet_; i++) {
		if (niz_[i] == nullptr) {
			niz_[i] = stvar;
			return (*this);
		}
	}
	throw Prepunjenje();
}

template <typename T> T *Zbirka<T*>::operator-=(const T &stvar) {
	for (int i = 0; i < kapacitet_; i++) {
		if (niz_[i] != nullptr && (*niz_[i]) == stvar) {
			T *povratna = niz_[i];
			niz_[i] = nullptr;
			return niz_[i];
		}
	}
	throw NemaTaj();
}

template<typename T> int Zbirka<T*>::brojSlobodnihMesta() const {
	int suma = 0;
	for (int i = 0; i < kapacitet_; i++) if (niz_[i] != nullptr) ++suma;
	return suma;
}

template <typename T> ostream &operator<<(ostream &izlaz, const Zbirka<T*> &z) {
	izlaz << "[";
	bool prvi = true;
	for (int i = 0; i < z.kapacitet_; i++) {
		if (z.niz_[i] != nullptr) {
			if (!prvi) izlaz << ",";
			izlaz << (*z.niz_[i]);
			prvi = false;
		}
	}
	izlaz << "]";
	return izlaz;
}

class PrevelikaZapremina : public exception {
public:
	const char *what() { return "U Skladistu nema mesta za proizvod te zapremine"; }
};

class Skladiste : public Zbirka<Proizvod*> {
private:
	double raspolozivaZapremina_;
public:
	Skladiste(int kapacitet, double zapremina): Zbirka(kapacitet), raspolozivaZapremina_(zapremina) {}
	double ukupnaZapremina() const;
	double slobodnaZaprenina() const { return raspolozivaZapremina_ - ukupnaZapremina(); }
	Skladiste &operator+=(Proizvod *stvar) {
		if (slobodnaZaprenina() < stvar->zapremina()) throw PrevelikaZapremina();
		Zbirka<Proizvod*>::operator+=(stvar);
		return (*this);
	}
};

double Skladiste::ukupnaZapremina() const {
	double suma = 0;
	for (int i = 0; i < kapacitet_; i++) if (niz_[i] != nullptr) suma += niz_[i]->zapremina();
	return suma;
}

int main(void) {
	try {
		Skladiste s(10, 100);
		s += new Sanduk(2, 3, 4);
		cout << s << endl;
		s += new Bure(1, 1);
		cout << s << endl;
		s += new Sanduk(1, 1, 1);
		cout << s << endl;
		Bure b(1, 1);
		s -= b;
		cout << s << endl;
	}
	catch (exception &e) { cerr << e.what(); }
	_getch();
}
