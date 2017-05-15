#ifndef _izuzeci_h_
#define _izuzeci_h_

#include <exception>

using namespace std;

class PunaZbirka : public exception {
public:
	const char *what() const override {
		return "Zbirka je puna";
	}
};

class NePostojiElement : public exception {
public:
	const char *what() const override {
		return "Ne postoji element na datom indeksu";
	}
};

#endif
