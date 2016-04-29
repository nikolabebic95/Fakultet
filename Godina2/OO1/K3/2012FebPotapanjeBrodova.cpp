// Tekst zadatka - http://home.etf.rs/~kraus/nastava/oop1/ispiti/isp_2012_02_09.html

#include <iostream>
#include <exception>
#include <conio.h>
#include <cstdlib>
#include <ctime>

using namespace std;

class IndeksVanOpsega : public exception {
	const char *what() const override { return "Ne postoji ta pozicija na tabli"; }
};

inline int slucajanBroj(int donja, int gornja) {
	return (int)((rand() / ((double)(RAND_MAX + 1)))*(gornja - donja + 1) + donja);
}

class Pozicija {
private:
	int vrsta_;
	int kolona_;
public:
	explicit Pozicija(int vrsta = 0, int kolona = 0): vrsta_(vrsta), kolona_(kolona) {}
	int vrsta() const { return vrsta_; }
	int kolona() const { return kolona_; }
	static Pozicija slucajna(int vrste, int kolone) { return Pozicija(slucajanBroj(0, vrste - 1), slucajanBroj(0, kolone - 1)); }
};

template <typename T> class Tabla {
private:
	T **matrica_;
	int brojVrsta_;
	int brojKolona_;
	
	void kopiraj(const Tabla &t);
	void premesti(Tabla &t) {
		matrica_ = t.matrica_;
		t.matrica_ = nullptr;
		brojVrsta_ = t.brojVrsta_;
		brojKolona_ = t.brojKolona_;
	}
	void brisi();

public:
	Tabla() : brojVrsta_(0), brojKolona_(0), matrica_(nullptr) {}
	Tabla(int brojVrsta, int brojKolona);
	Tabla(const Tabla &t) { kopiraj(t); }
	Tabla(Tabla &&) { premesti(t); }
	Tabla &operator=(const Tabla &t) {
		if (this != &t) {
			brisi();
			kopiraj();
		}
		return *this;
	}
	Tabla operator=(Tabla &&t) {
		brisi();
		premesti(t);
		return *this;
	}
	~Tabla() { brisi(); }
	int brojVrsta() const { return brojVrsta_; }
	int brojKolona() const { return brojKolona_; }
	void popuni(T t);
	T &operator[](Pozicija p) {
		if ((p.vrsta() < 0) && (p.vrsta() >= brojVrsta()) && (p.kolona() < 0) && (p.kolona() >= brojKolona())) throw IndeksVanOpsega();
		return matrica_[p.vrsta()][p.kolona()]; //svi su inline pa se ne zovu vise puta - ne zovu se nijednom
	} //namerno necu referencu na poziciju, dovoljno je mala da moze da kopira a ovako moze da se prosledi xvalue
	const T &operator[](Pozicija p) const { return const_cast<Tabla<T>&>(*this)[p]; }
	template <typename T> friend ostream &operator<<(ostream &izlaz, const Tabla<T> &t);
};

template<typename T> void Tabla<T>::kopiraj(const Tabla & t) {
	brojVrsta_ = t.brojVrsta_;
	brojKolona_ = t.brojKolona_;
	matrica_ = new T*[brojVrsta_];
	for (int i = 0; i < brojVrsta_; i++) matrica_[i] = new Polje[brojVrsta_];
	for (int i = 0; i < brojVrsta_; i++) for (int j = 0; j < brojKolona_; j++) matrica_[i][j] = t.matrica_[i][j];
}

template<typename T> void Tabla<T>::brisi() {
	if (matrica_ != nullptr) for (int i = 0; i < brojVrsta_; i++) delete[]matrica_[i];
	delete[]matrica_;
}

template<typename T> Tabla<T>::Tabla(int brojVrsta, int brojKolona): brojVrsta_(brojVrsta), brojKolona_(brojKolona) {
	matrica_ = new T*[brojVrsta];
	for (int i = 0; i < brojVrsta; matrica_[i++] = new T[brojKolona]);
}

template<typename T> void Tabla<T>::popuni(T t) {
	for (int i = 0; i < brojVrsta_; i++) for (int j = 0; j < brojKolona_; j++) matrica_[i][j] = t;
}

template<typename T> ostream & operator<<(ostream & izlaz, const Tabla<T>& t) {
	for (int i = -1; i <= t.brojVrsta_; i++) {
		for (int j = -1; j <= t.brojKolona_; j++) {
			if (i == -1 && j == -1) izlaz << (char)201; //gore levo
			else if (i == -1 && j == t.brojKolona()) izlaz << (char)187; //gore desno
			else if (i == t.brojVrsta() && j == -1) izlaz << (char)200; //dole levo
			else if (i == t.brojVrsta() && j == t.brojKolona()) izlaz << (char)188; //dole desno
			else if (i == -1 || i == t.brojVrsta()) izlaz << (char)205; //gore ili dole
			else if (j == -1 || j == t.brojKolona()) izlaz << (char)186; //levo ili desno
			else izlaz << t.matrica_[i][j];
		}
		izlaz << endl;
	}
	return izlaz;
}

struct Polje {
	enum Stanje { PRAZNO, PROMASAJ, BROD, POTOPLJEN };
	Stanje stanje_;
	Polje(Stanje stanje = PRAZNO): stanje_(stanje) {} //namerno nije explicit jer zasto ne bih zeleo konverziju
	friend ostream &operator<<(ostream &izlaz, const Polje &p) {
		if (p.stanje_ == Polje::PRAZNO) izlaz << " ";
		else if (p.stanje_ == Polje::PROMASAJ) izlaz << (char)247; //talasi
		else if (p.stanje_ == Polje::BROD) izlaz << (char)219; //belo polje
		else izlaz << (char)176; //polje sa retkim tackicama
		return izlaz;
	}
	friend bool operator==(const Polje &p1, const Polje &p2) { return p1.stanje_ == p2.stanje_; }
	friend bool operator!=(const Polje &p1, const Polje &p2) { return !(p1 == p2); }
};

class Igrac {
private:
	static int brojac_;
	int identifikator_ = brojac_++;
	Tabla<Polje> svoja_;
	int brojBrodova_;
	int brojPotopljenih_;
	Igrac *protivnik_ = nullptr;

	Igrac(const Igrac &) = delete;
	Igrac &operator=(const Igrac &) = delete;

protected:
	Tabla<Polje> tudja_; //mora da vidi tudju da bi mogao da zna sta da gadja
	virtual void pisi(ostream &izlaz) const { 
		izlaz << vrsta() << " " << identifikator_ << endl << endl << svoja_ << endl << tudja_ << endl << endl;
	}
public:
	Igrac() = default; //Uvek cu pozvati postaviPocetnoStanje, jer u konstruktoru ne bih mogao da zadam protivnika prvom
	virtual ~Igrac() {}
	virtual char vrsta() const = 0;
	void postaviPocetnoStanje(int vrste, int kolone, int brojBrodova, Igrac *protivnik);
	bool primiPotez(Pozicija p) {
		if (svoja_[p] == Polje::BROD) {
			svoja_[p] = Polje::POTOPLJEN;
			return true;
		}
		if (svoja_[p] == Polje::PRAZNO) svoja_[p] = Polje::PROMASAJ; //mora if jer sta ako gadja dvaput isto
		return false;
	}
	virtual Pozicija birajPoziciju() const = 0;
	bool odigrajPotez() {
		Pozicija gadjanje = birajPoziciju();
		bool pogodak = protivnik_->primiPotez(gadjanje);
		if (pogodak) {
			tudja_[gadjanje] = Polje::POTOPLJEN;
			brojPotopljenih_++;
			if (brojPotopljenih_ == brojBrodova_) return true;
		}
		else {
			if (tudja_[gadjanje] == Polje::PRAZNO) tudja_[gadjanje] = Polje::PROMASAJ;
		}
		return false;
	}
	friend ostream &operator<<(ostream &izlaz, const Igrac &i) {
		i.pisi(izlaz);
		return izlaz;
	}
};
int Igrac::brojac_ = 0;

// Upasce u mrtvu petlju ako se zada da ima vise brodova nego polja
void Igrac::postaviPocetnoStanje(int vrste, int kolone, int brojBrodova, Igrac * protivnik) {
	svoja_ = Tabla<Polje>(vrste, kolone);
	tudja_ = Tabla<Polje>(vrste, kolone);
	brojBrodova_ = brojBrodova;
	brojPotopljenih_ = 0;
	protivnik_ = protivnik;
	for (int i = 0; i < brojBrodova; i++) {
		Pozicija p = Pozicija::slucajna(vrste, kolone);
		if (svoja_[p] == Polje::PRAZNO) svoja_[p] = Polje::BROD;
		else --i;
	}
}

class Racunar : public Igrac {
public:
	char vrsta() const override { return 'R'; }
	Pozicija birajPoziciju() const override;
};

Pozicija Racunar::birajPoziciju() const {
	Pozicija povratna = Pozicija::slucajna(tudja_.brojVrsta(), tudja_.brojKolona());
	while (tudja_[povratna] != Polje::PRAZNO) povratna = Pozicija::slucajna(tudja_.brojVrsta(), tudja_.brojKolona());
	return povratna;
}

class Covek : public Igrac {
public:
	char vrsta() const override { return 'C'; }
	Pozicija birajPoziciju() const override {
		int i, j;
		cin >> i >> j;
		return Pozicija(i, j);
	}
};

int main(void) {
	try {
		time_t t;
		srand((unsigned)time(&t));
		Racunar r1, r2;
		r1.postaviPocetnoStanje(4, 4, 4, &r2);
		r2.postaviPocetnoStanje(4, 4, 4, &r1);
		while (true) {
			bool b;
			b = r1.odigrajPotez();
			cout << r1;
			if (b) break;
			b = r2.odigrajPotez();
			cout << r2;
			if (b) break;
		}
	}
	catch (exception &e) { cerr << e.what(); }
	_getch();
}

