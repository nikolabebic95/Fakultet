#include "MernaOblast.h"

MernoMesto MernaOblast::najmanjaTemperatura() const {
	if (niz_.brojPopunjenih() == 0) throw PraznaOblast();
	int indeks = 0;
	double najmanja = niz_[0].srednjaVrednost();
	for (int i = 1; i < niz_.brojPopunjenih(); i++) {
		double temp;
		if ((temp = niz_[i].srednjaVrednost()) < najmanja) {
			indeks = i;
			najmanja = temp;
		}
	}
	return niz_[indeks];
}

ostream &operator<<(ostream &izlaz, const MernaOblast &m) {
	for (int i = 0; i < m.niz_.brojPopunjenih(); cout << m.niz_[i++] << endl);
	return izlaz;
}