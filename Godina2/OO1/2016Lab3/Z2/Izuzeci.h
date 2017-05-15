#ifndef _izuzeci_h_
#define _izuzeci_h_

#include <exception>

using namespace std;

class IndeksVanOpsega : public exception {
public:
	const char *what() const override {
		return "Indeks niza je van opsega";
	}
};

class PostojiDatoteka : public exception {
public:
	const char *what() const override {
		return "Datoteka vec postoji";
	}
};

#endif
