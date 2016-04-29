#ifndef _kvadar_h_
#define _kvadar_h_

#include <iostream>

using namespace std;

class Kvadar {
private:
	double a_, b_, c_;

public:
	Kvadar(double a = 1, double b = 1, double c = 1) : a_(a), b_(b), c_(c) {}

	friend bool operator==(const Kvadar &a, const Kvadar &b) { return a.a_ == b.a_ && a.b_ == b.b_ && a.c_ == b.c_; }

	friend bool operator!=(const Kvadar &a, const Kvadar &b) { return !(a == b); }

	friend ostream &operator<<(ostream &izlaz, const Kvadar &k) {
		izlaz << "K(" << k.a_ << "," << k.b_ << "," << k.c_ << ")";
		return izlaz;
	}
};

#endif