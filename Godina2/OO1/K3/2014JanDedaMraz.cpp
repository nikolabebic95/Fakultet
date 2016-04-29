// Tekst zadatka - http://rti.etf.bg.ac.rs/rti/ir2oo1/rokovi/OO1I140116.pdf

#include <iostream>
#include <string>
#include <exception>
#include <conio.h>

using namespace std;

class NemaNista : public exception {
public:
	const char *what() const override { return "Ne moze se uzeti iz prazne zbirke"; }
};

class PogresnoSlovo : public exception {
public:
	const char *what() const override { return "Oznaka pola mora biti 'M' ili 'Z'"; }
};

class GreskePaketic : public exception {};

class PrekoracenjeCene : public GreskePaketic {
public:
	const char *what() const override { return "Cena tog poklona je prevelika za taj paketic"; }
};

class PogresanPol : public GreskePaketic {
public:
	const char *what() const override { return "Taj poklon nije namenjen ovom paketicu"; }
};

class Dete {
private:
	char pol_; //glupost al koga briga
	string ime_;
	Dete(const Dete &) = delete;
	Dete &operator=(const Dete &) = delete;

public:
	Dete(char pol, string ime) : pol_(pol), ime_(ime) { if ((pol != 'M') && (pol!='Z')) throw PogresnoSlovo(); }
	char getPol() const { return pol_; }
	string getIme() const { return ime_; }
	friend ostream &operator<<(ostream &izlaz, const Dete &d) {
		izlaz << d.ime_ << ":" << d.pol_;
		return izlaz;
	}

};

class Poklon {
private:
	static int brojac_;
	int id_;
	double cena_;

protected:
	virtual void pisi(ostream &izlaz) const { izlaz << getVrsta() << "." << id_ << "(" << cena_ << ")"; }
	//ne mora ovako u ovom zadatku ali sto da ne
public:
	Poklon(double cena) :cena_(cena), id_(brojac_++) {}
	Poklon(const Poklon &p) { id_ = brojac_++; cena_ = p.cena_; }
	Poklon &operator=(const Poklon &p) { id_ = brojac_++; cena_ = p.cena_; }
	virtual char getVrsta() const = 0;
	virtual char getPol() const = 0;
	virtual double getCena() const { return cena_; }
	virtual Poklon *klonirajSe() const = 0;
	friend ostream &operator<<(ostream &izlaz, const Poklon &p) {
		p.pisi(izlaz);
		return izlaz;
	}
	virtual ~Poklon() {}
};
int Poklon::brojac_ = 0;

class Autic : public Poklon {
public:
	Autic(double cena): Poklon(cena) {}
	char getVrsta() const override { return 'A'; }
	char getPol() const override { return 'M'; }
	Autic *klonirajSe() const override { return new Autic(*this); }
};

class Lutka : public Poklon {
public:
	Lutka(double cena) :Poklon(cena) {}
	char getVrsta() const override { return 'L'; }
	char getPol() const override { return 'Z'; }
	Lutka *klonirajSe() const override { return new Lutka(*this); }
};

class Ukras : public Poklon {
public:
	Ukras(double cena) :Poklon(cena) {}
	char getVrsta() const override { return 'U'; }
	char getPol() const override { return '?'; }
	Ukras *klonirajSe() const override { return new Ukras(*this); }
};

template <typename T> class Zbirka; //da bi morali pokazivaci
template <typename T> class Zbirka<T*> {
private:
	struct Clan {
		T *info_;
		Clan *sled_;
		Clan(T *info) : info_(info), sled_(nullptr) {}
	};

	Clan *prvi_;
	Clan *posl_;
	int brojClanova_ ;

	void kopiraj(const Zbirka &z);
	void premesti(Zbirka &z) {
		brojClanova_ = z.brojClanova_;
		prvi_ = z.prvi_;
		posl_ = z.posl_;
		z.prvi_ = nullptr;
		z.posl_ = nullptr;
	}
	void brisi();
	
public:
	Zbirka(): prvi_(nullptr), posl_(nullptr), brojClanova_(0) {}
	Zbirka(const Zbirka &z) { kopiraj(z); }
	Zbirka(Zbirka &&z) { premesti(z); }
	Zbirka &operator=(const Zbirka &z) {
		if (this != &z) {
			brisi();
			kopiraj(z);
		}
		return *this;
	}
	Zbirka &operator=(Zbirka &&z) { premesti(z); }
	~Zbirka() { brisi(); }

	virtual Zbirka &operator+=(T *t) {
		Clan *novi = new Clan(t);
		if (prvi_ == nullptr) prvi_ = novi;
		else posl_->sled_ = novi;
		posl_ = novi;
		brojClanova_++;
		return (*this);
	}
	T* uzmi() {
		if (brojClanova_ == 0) throw NemaNista();
		Clan *brisanje = prvi_;
		T* povratna = prvi_->info_;
		prvi_ = prvi_->sled_;
		brojClanova_--;
		delete brisanje;
		return povratna;
	}
	int getBrojClanova() const { return brojClanova_; }
	template <typename T> friend ostream &operator<<(ostream &izlaz, const Zbirka<T*> &z);
	
};

template <typename T> void Zbirka<T*>::kopiraj(const Zbirka &z) {
	Clan *tek = z.prvi_;
	while (tek != nullptr) (*this) += tek->info_->klonirajSe();
}

template <typename T> void Zbirka<T*>::brisi() {
	while (brojClanova_ != 0) delete uzmi();
}

template <typename T> ostream &operator<<(ostream &izlaz, const Zbirka<T*> &z) {
	izlaz << "[";
	Zbirka<T*>::Clan *tek = z.prvi_;
	for (int i = 0; i < z.brojClanova_; i++) {
		izlaz << *(tek->info_);
		tek = tek->sled_;
		if (i != z.brojClanova_ - 1) izlaz << ",";
	}
	izlaz << "]";
	return izlaz;
}

class Magacin : public Zbirka<Poklon*> {
private:
	Magacin(const Magacin &) = delete;
	Magacin &operator=(const Magacin &) = delete;
public:
	Magacin() = default;
};

class Paketic : public Zbirka<Poklon*> {
private:
	char pol_;
	double maxCena_;
	double trenutnaCena_;

	bool dozvoljeno(Poklon *p) {
		if (p->getPol() == '?') return true;
		if (pol_ == p->getPol()) return true;
		return false;
	}

public:
	Paketic(char pol, double maxCena): pol_(pol), maxCena_(maxCena), trenutnaCena_(0) {}
	Paketic &operator+=(Poklon *p) override {
		if (maxCena_ < trenutnaCena_ + p->getCena()) throw PrekoracenjeCene();
		if (dozvoljeno(p)) {
			Zbirka<Poklon*>::operator+=(p);
			trenutnaCena_ += p->getCena();
		}
		else throw PogresanPol();
		return (*this);
	}
	double getMaxCena() const { return maxCena_; }
	double getTrenutnaCena() const { return trenutnaCena_; }
};

class DedaMraz {
public:
	Paketic *operator()(double cena, const Dete &dete, Magacin &magacin) {
		Paketic *povratna = new Paketic(dete.getPol(), cena);
		Poklon *kandidat;
		int n = magacin.getBrojClanova();
		for (int i = 0; i < n; i++) {
			kandidat = magacin.uzmi();
			try { 
				*povratna += kandidat; 
			}
			catch (GreskePaketic &) {
				magacin += kandidat;
			}
			if (povratna->getMaxCena() == povratna->getTrenutnaCena()) break;
		}//mora petlja cak i za prekoracenje jer mozda posle trenutnog paketica ima neki jeftiniji koji moze da upadne
		return povratna;
	}
};

int main(void) {
	Magacin m;
	m += new Autic(1000);
	m += new Lutka(200);
	m += new Ukras(500);
	m += new Autic(800);
	m += new Lutka(300);
	m += new Ukras(400);

	cout << "Magacin: " << m << endl << endl;
	Dete d('M', "Nikola");

	DedaMraz HoHoHo;
	Paketic *p = HoHoHo(2500, d, m);

	cout << "Dete: " << d << endl << endl;
	cout << "Paketic: " << *p << endl << endl;
	cout << "Magacin: " << m << endl << endl;

	delete p;

	_getch();
}

