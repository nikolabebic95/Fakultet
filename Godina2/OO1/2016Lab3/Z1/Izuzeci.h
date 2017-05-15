#ifndef _izuzeci_h_
#define _izuzeci_h_

#include <exception>

using namespace std;

class PraznaLista : public exception {
	const char *what() const override {
		return "Lista je prazna";
	}
};

#endif
