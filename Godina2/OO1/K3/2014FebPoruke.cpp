// Tekst zadatka - http://home.etf.rs/~kraus/nastava/oop1/ispiti/isp_2014_02_06.html

#include <iostream>
#include <exception>
#include <utility>
#include <conio.h>

using namespace std;

class Prepunjenje : public exception {
public:
	const char *what() const override { return "Ne moze se dodati element u punu sekvencu"; }
};

class IndeksVanOpsega : public exception {
public:
	const char *what() const override { return "Na tom indeksu ne postoji element"; }
};

template <typename T> class Sekvenca {
public:
	explicit Sekvenca(int kapacitet) : kapacitet_(kapacitet), broj_clanova_(0) { niz_ = new T[kapacitet_]; }
	Sekvenca(const Sekvenca &s) { kopiraj(s); }
	Sekvenca(Sekvenca &&s) { premesti(s); }
	Sekvenca &operator=(const Sekvenca &s) {
		if (this != &s) {
			brisi();
			kopiraj(s);
		}
		return *this;
	}
	Sekvenca &operator=(Sekvenca &&s) {
		brisi();
		premesti(s);
		return *this;
	}
	virtual ~Sekvenca() { brisi(); }
	int brojClanova() const { return broj_clanova_; }
	int kapacitet() const { return kapacitet_; }
	Sekvenca &operator+=(T stvar) {
		if (broj_clanova_ == kapacitet_) throw Prepunjenje();
		niz_[broj_clanova_++] = stvar;
		return *this;
	}
	T &operator[](int indeks) {
		if (indeks < 0 || indeks > broj_clanova_) throw IndeksVanOpsega();
		return niz_[indeks];
	}
	const T &operator[](int indeks) const { return const_cast<Sekvenca&>(*this)[indeks]; }

private:
	T* niz_;
	int kapacitet_;
	int broj_clanova_;

	void kopiraj(const Sekvenca &s);
	void premesti(Sekvenca &s) {
		niz_ = s.niz_;
		s.niz_ = nullptr;
		kapacitet_ = s.kapacitet_;
		broj_clanova_ = s.broj_clanova_;
	}
	void brisi() {
		delete[]niz_;
		niz_ = nullptr;
	}
};

template<typename T> void Sekvenca<T>::kopiraj(const Sekvenca & s) {
	kapacitet_ = s.kapacitet_;
	broj_clanova_ = s.broj_clanova_;
	niz_ = new T[kapacitet_];
	for (int i = 0; i < broj_clanova_; i++) niz_[i] = s.niz_[i];
}

class Poruka : public Sekvenca<int> {
public:
	Poruka(int duzina): Sekvenca(duzina) {}
	friend ostream &operator<<(ostream &izlaz, const Poruka &p);
};

ostream & operator<<(ostream & izlaz, const Poruka & p) {
	for (int i = 0; i < p.brojClanova(); izlaz << p[i++] << endl);
	return izlaz;
}

class Kodek {
public:
	virtual ~Kodek() {}
	virtual Kodek &operator<<(Poruka &p) = 0;
	virtual Kodek &operator>>(Poruka &p) = 0;
	const Kodek &operator<<(Poruka &p) const {
		const_cast<Kodek&>(*this) << p;
		return *this;
	}
	const Kodek &operator>>(Poruka &p) const {
		const_cast<Kodek&>(*this) >> p;
		return *this;
	}
	virtual Kodek *klonirajSe() const = 0;
};

class Simetrican : public Kodek {
public:
	Kodek &operator>>(Poruka &p) override {
		(*this) << p;
		return *this;
	}
	virtual ~Simetrican() {}
};

class Eksili : public Simetrican {
public:
	explicit Eksili(int x): x_(x) {}
	Eksili &operator<<(Poruka &p) override;
	Eksili *klonirajSe() const { return new Eksili(*this); }
private:
	int x_;
};

Eksili & Eksili::operator<<(Poruka & p) {
	for (int i = 0; i < p.brojClanova(); i++)
		p[i] ^= x_;
	return *this;
}

class Zamena : public Simetrican {
public:
	Zamena &operator<<(Poruka &p);
	Zamena *klonirajSe() const { return new Zamena(*this); }
};

Zamena & Zamena::operator<<(Poruka & p) {
	for (int i = 0; i < p.brojClanova() / 2; i++) {
		int t = p[i];
		p[i] = p[p.brojClanova() - i - 1];
		p[p.brojClanova() - i - 1] = t;
	}
	return *this;
}

class Slozen : public Kodek {
public:
	Slozen(int duzina): kodeci_(duzina) {}
	Slozen(const Slozen &s) : kodeci_(s.kodeci_) { kloniraj(); }
	Slozen(Slozen &&s): kodeci_(move(s.kodeci_)) {}
	Slozen &operator=(const Slozen &s) {
		if (this != &s) {
			kodeci_ = s.kodeci_;
			kloniraj();
		}
		return (*this);
	}
	Slozen &operator=(Slozen &&s) {
		kodeci_ = move(s.kodeci_);
		return *this;
	}
	~Slozen();
	Slozen &operator<<(Poruka &p);
	Slozen &operator>>(Poruka &p);
	Slozen *klonirajSe() const { return new Slozen(*this); }
	Slozen &operator+=(Kodek *stvar) {
		kodeci_+=(stvar->klonirajSe());
		return *this;
	}
private:
	Sekvenca<Kodek*> kodeci_;

	void kloniraj();
};

Slozen::~Slozen() {
	for (int i = 0; i < kodeci_.brojClanova(); i++) delete kodeci_[i];
	//pozvace destruktor za sekvencu kodeka koji ce da dealocira niz
}

Slozen & Slozen::operator<<(Poruka & p) {
	for (int i = 0; i < kodeci_.brojClanova(); *kodeci_[i++] << p);
	return *this;
}

Slozen & Slozen::operator>>(Poruka & p) {
	for (int i = kodeci_.brojClanova() - 1; i >= 0; *kodeci_[i--] >> p);
	return *this;
}

void Slozen::kloniraj(){
	for (int i = 0; i < kodeci_.brojClanova(); i++) kodeci_[i] = kodeci_[i]->klonirajSe();
}

int main(void) {
	try {
		Poruka p(5);
		p += 0;
		p += -1;
		p += 1;

		Slozen s(3);
		Eksili s1(-1);
		Zamena s2;
		s += &s1;
		s += &s2;

		s << p;
		cout << p << endl;
		s >> p;
		cout << p << endl;
	}
	catch (exception &e) { cerr << e.what(); }
	_getch();
	
}


