// Tekst zadatka - http://home.etf.rs/~kraus/nastava/oop1/ispiti/isp_2013_02_07.html

#include <iostream>
#include <exception>
#include <conio.h>

using namespace std;

class VecPostojiSlovo : public exception {
public:
	const char *what() const override { return "Ne moze se dodati podatak sa tom oznakom jer vec postoji u zbirci"; }
};

class NemaMesta : public exception {
public:
	const char *what() const override { return "Nema slobodnog mesta u zbirci"; }
};

class NePostoji : public exception {
public:
	const char *what() const override { return "Ne postoji proizvod sa tom oznakom"; }
};

class NemaSirovine : public exception {
public:
	const char *what() const override { return "Nema dovoljno sirovine za proizvodnju tog proizvoda"; }
};

class Proizvod {
private:
	static int brojac_;
	int id_ = brojac_++;
protected:
	virtual void pisi(ostream &izlaz) const { izlaz << "[" << id_ << "]"; }
public:
	virtual double zapremina() const = 0;
	virtual Proizvod *klonirajSe() const = 0;
	friend ostream &operator<<(ostream &izlaz, const Proizvod &p) {
		p.pisi(izlaz);
		return izlaz;
	}
	virtual ~Proizvod() {}
};
int Proizvod::brojac_ = 0;

class Zica : public Proizvod {
private:
	double duzina_;
	double poprecniPresek_;
protected:
	void pisi(ostream &izlaz) const override {
		Proizvod::pisi(izlaz);
		izlaz << "Zica(" << duzina_ << "," << poprecniPresek_ << ")";
	}
public:
	Zica(double duzina, double poprecniPresek): duzina_(duzina), poprecniPresek_(poprecniPresek) {}
	double zapremina() const override { return duzina_*poprecniPresek_; }
	Zica *klonirajSe() const override { return new Zica(*this); }
};

class Sipka : public Proizvod {
private:
	double duzina_;
	double sirina_;
protected:
	void pisi(ostream &izlaz) const override {
		Proizvod::pisi(izlaz);
		izlaz << "Sipka(" << duzina_ << "," << sirina_ << ")";
	}
public:
	Sipka(double duzina, double sirina): duzina_(duzina), sirina_(sirina) {}
	double zapremina() const override { return duzina_*sirina_*sirina_; }
	Sipka *klonirajSe() const override { return new Sipka(*this); }
};

template <typename T> class Zbirka {
private:
	struct Par {
		char slovo_;
		T *pokazivac_;
		Par(): pokazivac_(nullptr) {}
		Par(char slovo, T *pokazivac): slovo_(slovo), pokazivac_(pokazivac) {}
	};

	Par *niz_;
	int kapacitet_;

	void kopiraj(const Zbirka &z);
	void premesti(Zbirka &&z) {
		niz_ = z.niz_;
		z.niz_ = nullptr;
		kapacitet_ = z.kapacitet_;
	}
	void brisi();

public:
	explicit Zbirka(int kapacitet = 10) : kapacitet_(kapacitet) { niz_ = new Par[kapacitet]; }
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
		brisi();
		premesti(z);
	}
	~Zbirka() { brisi(); }
	void operator()(char slovo, const T *pokazivac);
	T *operator[](char slovo) const;
	template <typename T> friend ostream &operator<<(ostream &izlaz, const Zbirka<T> &z);
};

template<typename T> void Zbirka<T>::kopiraj(const Zbirka &z) {
	kapacitet_ = z.kapacitet_;
	niz_ = new Par[kapacitet_];
	for (int i = 0; i < kapacitet_; i++) {
		if (z.niz_[i].pokazivac_ == nullptr) break;
		niz_[i] = z.niz_[i].pokazivac_->klonirajSe();
	}
}

template<typename T> void Zbirka<T>::brisi() {
	for (int i = 0; i < kapacitet_; i++) {
		if (niz_[i].pokazivac_ == nullptr) break;
		delete niz_[i].pokazivac_;
	}
	delete[]niz_;
}

template <typename T> void Zbirka<T>::operator()(char slovo, const T *pokazivac) {
	for (int i = 0; i < kapacitet_; i++) if ((niz_[i].pokazivac_ != nullptr) && (slovo == niz_[i].slovo_)) throw VecPostojiSlovo();
	for (int i = 0; i < kapacitet_; i++) {
		if (niz_[i].pokazivac_ == nullptr) {
			niz_[i].slovo_ = slovo;
			niz_[i].pokazivac_ = pokazivac->klonirajSe();
			return;
		}
	}
	throw NemaMesta();
}

template<typename T> T *Zbirka<T>::operator[](char slovo) const {
	for (int i = 0; i < kapacitet_; i++) {
		if (niz_[i].pokazivac_ == nullptr) return nullptr;
		if (niz_[i].slovo_ == slovo) return niz_[i].pokazivac_->klonirajSe();
	}
	return nullptr;
}

template <typename T> ostream &operator<<(ostream &izlaz, const Zbirka<T> &z) {
	for (int i = 0; i < z.kapacitet_; i++) {
		if (z.niz_[i].pokazivac_ == nullptr) break;
		izlaz << "(" << z.niz_[i].slovo_ << ") " << (*z.niz_[i].pokazivac_) << endl;
	}
	return izlaz;
}

class Fabrika {
private:
	Zbirka<Proizvod> zbirka_;
	double zapreminaSirovine_;
	int brojProizvedenih_;
public:
	explicit Fabrika(int kapacitet): zbirka_(kapacitet), zapreminaSirovine_(0), brojProizvedenih_(0) {}
	void operator()(char slovo, Proizvod *proizvod) { zbirka_(slovo, proizvod); }
	Fabrika &operator+=(double sirovina) {
		zapreminaSirovine_ += sirovina;
		return (*this);
	}
	Proizvod *proizvedi(char slovo) {
		Proizvod *povratna = zbirka_[slovo];
		if (povratna == nullptr) throw NePostoji();
		if (povratna->zapremina()*1.1 <= zapreminaSirovine_) {
			zapreminaSirovine_ -= povratna->zapremina();
			return povratna;			
		}
		delete povratna;
		throw NemaSirovine();
	}
	friend ostream &operator<<(ostream &izlaz, const Fabrika &f) {
		izlaz << f.zbirka_ << endl << f.brojProizvedenih_ << endl << f.zapreminaSirovine_ << endl;
		return izlaz;
	}
};

int main(void) {
	try {
		Fabrika f(5);
		f += 1000;
		Zica z(5, 2);
		f('z', &z);
		Sipka s1(5, 1);
		f('s', &s1);
		Sipka s2(3, 2);
		f('x', &s2);
		delete f.proizvedi('x');
		cout << f << endl;
	}
	catch (exception &e) { cerr << e.what(); }
	_getch();
}

