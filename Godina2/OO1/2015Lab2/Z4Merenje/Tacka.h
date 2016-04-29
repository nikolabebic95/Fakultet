#ifndef _tacka_h_
#define _tacka_h_

#include <cmath>
#include <iostream>

using namespace std;

class Tacka {
private:
	double x_, y_, z_;

public:
	Tacka(double x = 0, double y = 0, double z = 0) : x_(x), y_(y), z_(z) {}

	virtual ~Tacka() {}

	friend double operator-(const Tacka &a, const Tacka &b) {
		double x = a.x_ - b.x_;
		double y = a.y_ - b.y_;
		double z = a.z_ - b.z_;
		return sqrt(x*x + y*y + z*z);
	}

	friend ostream &operator<<(ostream &izlaz, const Tacka &t) {
		izlaz << "(" << t.x_ << "," << t.y_ << "," << t.z_ << ")";
		return izlaz;
	}

};

#endif