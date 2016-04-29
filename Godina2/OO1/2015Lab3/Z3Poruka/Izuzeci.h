#ifndef _izuzeci_h_
#define _izuzeci_h_

#include <exception>

using namespace std;

class Prepunjenje : public exception {
public:
	const char *what() const override {
		return "Zbirka je vec puna";
	}
};

class VecPostoji : public exception {
public:
	const char *what() const override {
		return "Kljuc vec postoji u zbirci";
	}
};

class NePostoji : public exception {
public:
	const char *what() const override {
		return "Ne postoji taj kljuc u zbirci";
	}
};

#endif