#ifndef _proizvod_h_
#define _proizvod_h_

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class Proizvod {
private:
	string naziv_;
	double cena_;
public:
	Proizvod(string naziv, double cena) : naziv_(naziv), cena_(cena) {}
	Proizvod() = default;
	friend ostream &operator<<(ostream &izlaz, const Proizvod &p) {
		izlaz << p.naziv_ << "("  << p.cena_ << ")";
		return izlaz;
	}
};

#endif