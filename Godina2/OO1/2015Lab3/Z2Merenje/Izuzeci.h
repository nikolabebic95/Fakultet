#ifndef _izuzeci_h_
#define _izuzeci_h_

#include <exception>

using namespace std;

class Prepunjenje : public exception {
public:
	const char *what() const override {
		return "Pokusaj dodavanja elementa u pun niz";
	}
};

class LosIndeks : public exception {
public:
	const char *what() const override {
		return "Pokusaj dohvatanja elementa sa mesta koje nije u opsegu";
	}
};

class LoseVreme : public exception {
public:
	const char *what() const override {
		return "Pokusaj kreiranja merenja sa nekorektnim vremenom";
	}
};

class LosaTemperatura : public exception {
public:
	const char *what() const override {
		return "Pokusaj kreiranja merenja sa nekorektnom temperaturom";
	}
};

class PraznaOblast : public exception {
public:
	const char *what() const override {
		return "Ne moze se izracunati najniza temperatura u praznoj oblasti";
	}
};

#endif