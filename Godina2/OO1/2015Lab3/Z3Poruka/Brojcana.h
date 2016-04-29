#ifndef _brojcana_h_
#define _brojcana_h_

#include "Poruka.h"

using namespace std;

class Brojcana : public Poruka {
private:
	int broj_;
protected:
	void pisi(ostream &izlaz) const override { izlaz << broj_; }
public:
	Brojcana(int broj): broj_(broj) {} //nije explicit jer hocu da konvertuje broj u brojcanu poruku
	Brojcana() = default;
};

#endif