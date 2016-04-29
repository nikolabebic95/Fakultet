#ifndef _posiljalac_h_
#define _posiljalac_h_

#include <string>
#include <iostream>

using namespace std;

class Posiljalac {
private:
	string ime_;

	Posiljalac(const Posiljalac &) = delete;
	Posiljalac &operator=(const Posiljalac &) = delete;

public:
	Posiljalac(string ime) : ime_(ime) {}
	Posiljalac() = default;
	friend bool operator==(const Posiljalac &x, const Posiljalac &y) { return x.ime_ == y.ime_; }
	friend bool operator!=(const Posiljalac &x, const Posiljalac &y) { return !(x == y); }
	friend ostream &operator<<(ostream &izlaz, const Posiljalac &p) {
		izlaz << p.ime_;
		return izlaz;
	}
};

#endif