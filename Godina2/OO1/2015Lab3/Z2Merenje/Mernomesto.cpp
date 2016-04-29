#include "MernoMesto.h"

double MernoMesto::srednjaVrednost() const {
	double suma = 0;
	for (int i = 0; i < niz_.brojPopunjenih(); suma += niz_[i++].getTemperatura());
	return suma / niz_.brojPopunjenih();
}