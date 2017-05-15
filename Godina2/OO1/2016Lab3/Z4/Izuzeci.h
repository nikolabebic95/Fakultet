#ifndef _izuzeci_h_
#define _izuzeci_h_

#include <exception>

using namespace std;

class IndeksVanOpsega : public exception {
public:
	const char *what() const override {
		return "Indeks van opsega";
	}
};

#endif
