#ifndef _mernaoblast_h_
#define _mernaoblast_h_

#include "Niz.h"
#include "MernoMesto.h"
#include <iostream>

using namespace std;

class MernaOblast {
private:
	Niz<MernoMesto> niz_;

public:
	explicit MernaOblast(int kapacitet) : niz_(kapacitet) {}
	MernaOblast() = default;
	MernaOblast &operator+=(MernoMesto m) { niz_ += m; return (*this); }
	MernoMesto najmanjaTemperatura() const;
	friend ostream &operator<<(ostream &izlaz, const MernaOblast &m);
};

#endif