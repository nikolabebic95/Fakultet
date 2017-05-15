#include<iostream>
using namespace std;
class Kupa
{
public:
	Kupa(double rr = 1.0, double hh = 2.0)
		:r(rr), h(hh)
	{
		if (r < 0 || h < 0) exit(1);
	}
	virtual double V() const
	{
		return r*r*PI*h / 3;
	}
	virtual Kupa* makeCopy() const
		/*Posto skladiste sadrzi pokazivace ili reference na kupe
		radi bezbednosti, potrebno je da u skladiste stavimo kopije
		stvarnih objekata, jer originalni objekti mogu biti unisteni
		pre skladista. Ova metoda pravi kopiju*/
	{
		return new Kupa(r, h);
	}
	friend bool operator<(const Kupa &k1, const Kupa &k2)
	{
		return k1.V() < k2.V();
	}
	virtual void ispisi(ostream &out) const
	{
		out << r << ',' << h;
	}
	friend ostream& operator<<(ostream &out, const Kupa &k)
	{
		k.ispisi(out);
		return out;
	}
protected:
	double r;
	double h;
	const double PI = 3.141592;
};
class ZarubljenaKupa : public Kupa
{
public:
	ZarubljenaKupa(double r, double h, double dd)
		:Kupa(r, h), d(dd)
	{
		if (d > h) exit(1);
	}
	virtual double V() const override
	{
		return r*r*PI*(h*h*h - d*d*d) / 3 / h / h;
	}
	virtual void ispisi(ostream &out) const override
	{
		Kupa::ispisi(out);
		out << ',' << d;
	}
	virtual Kupa* makeCopy() const override
	{
		return new ZarubljenaKupa(r, h, d);
	}
protected:
	double d;
};
class Skladiste
{
	struct Elem
	{
		Elem *next;
		Kupa *k;
		Elem(const Kupa &ku)
		{
			next = nullptr;
			k = ku.makeCopy();
		}
		~Elem()
		{
			delete k;
		}
	};
	Elem *first = nullptr;
public:
	Skladiste()
		:first(nullptr)
	{

	}
	Skladiste(const Skladiste&) = delete;
	Skladiste(Skladiste&&) = delete;
	Skladiste &operator=(const Skladiste&) = delete;
	Skladiste &operator=(Skladiste&&) = delete;
	Skladiste &operator+=(const Kupa &k)
	{
		Elem *newElem = new Elem(k);
		newElem->next = first;
		first = newElem;
		return *this;
	}
	int operator()(double vlow, double vh) const
	{
		int count = 0;
		Elem *current = first;
		while (current != nullptr)
		{
			if (current->k->V() >= vlow && current->k->V() <= vh) count++;
			current = current->next;
		}
		return count;
	}
	friend ostream& operator<<(ostream &out, const Skladiste &s)
	{
		Elem *current = s.first;
		out << '[';
		while (current != nullptr && current->next != nullptr)
		{
			out << *(current->k);
			out << '|';
			current = current->next;
		}
		if (current != nullptr) out << *(current->k);;
		out << ']';
		return out;
	}
	~Skladiste()
	{
		Elem *current = first;
		while (current != nullptr)
		{
			Elem *nx = current->next;
			delete current;
			current = nx;
		}
		first = nullptr;
	}
};
int main()
{
	int brKupa;
	cout << "Unesite broj kupa (0 za kraj): ";
	cin >> brKupa;
	while (brKupa > 0)
	{
		Skladiste s;
		for (int i = 0; i < brKupa; i++)
		{
			int tip;
			cout << "Unesite tip kupe (1-obicna, 2-zarubljena): ";
			cin >> tip;
			double r, h, d;
			switch (tip)
			{
			case 1:
				cout << "Unesite dimenzije: ";
				cin >> r >> h;
				s += Kupa(r, h);
				break;
			case 2:
				cout << "Unesite dimenzije: ";
				cin >> r >> h>>d;
				s += ZarubljenaKupa(r, h, d);
				break;
			default:
				cout << "Neispravan tip\n";
				i--;
				break;
			}
		}
		cout << s;
		double low, high;
		cout << "Unesite granice zapremine: ";
		cin >> low >> high;
		cout << "Postoji " << s(low, high) << " kupa za zapreminom u tim granicama\n";
		cout << "Unesite broj kupa (0 za kraj): ";
		cin >> brKupa;
	}
}