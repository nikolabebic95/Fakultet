#ifndef _tekstualna_h_
#define _tekstualna_h_

#include "Poruka.h"
#include <string>

using namespace std;

class Tekstualna : public Poruka {
private:
	string tekst_;
	
protected:
	void pisi(ostream &izlaz) const override { izlaz << tekst_; }

public:
	Tekstualna(string tekst) : tekst_(tekst) {}
	Tekstualna() = default;
};

#endif