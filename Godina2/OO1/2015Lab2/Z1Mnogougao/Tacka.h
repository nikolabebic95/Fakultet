#ifndef _tacka_h_
#define _tacka_h_

#include <iostream>
#include <cmath>

using namespace std;

class Tacka {
private:
	double x_, y_, z_;

protected:

	virtual void pisi(ostream &izlaz) const {
		izlaz << "(" << x_ << "," << y_ << "," << z_ << ")";
	}


public:

	Tacka(double x = 0, double y = 0, double z = 0) : x_(x), y_(y), z_(z) {}

	virtual ~Tacka() {}

	virtual Tacka *klonirajSe_() const {
		Tacka *nova = new Tacka(*this);
		return nova;
	}

	friend double operator-(const Tacka &a, const Tacka &b) {
		double x = a.x_ - b.x_;
		double y = a.y_ - b.y_;
		double z = a.z_ - b.z_;
		return sqrt(x*x + y*y + z*z);
	}

	virtual double udaljenost() const { return *this - Tacka(); }


	friend ostream &operator<<(ostream &izlaz, const Tacka &t) {
		t.pisi(izlaz);
		return izlaz;
	}

};
#endif