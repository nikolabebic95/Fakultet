#ifndef _izuzeci_h_
#define _izuzeci_h_

#include <exception>

using namespace std;

//nista nema noexcept jer se VS2013 buni, u VS2015 je radilo

class NemaMesta : public exception {
public:
	const char *what() const override {
		return "Nema mesta na polici da se doda stvar";
	}
};

class Preopterecenje : public exception {
public:
	const char *what() const override {
		return "Dodavanje stvari bi preopteretilo nosivost police";
	}
};

class LosIndeks : public exception {
public:
	const char *what() const override {
		return "Indeks niza nije u opsegu";
	}
};

#endif