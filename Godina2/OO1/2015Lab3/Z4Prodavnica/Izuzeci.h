#ifndef _izuzeci_h_
#define _izuzeci_h_

#include <exception>

using namespace std;

class Prepunjenje : public exception {
public:
	const char *what() const override {
		return "Prodavnica je puna, ne moze se dodati artikal";
	}
};

class NemaNista : public exception {
public:
	const char *what() const override {
		return "Prodavnica je prazna, ne moze se uzeti artikal";
	}
};

#endif