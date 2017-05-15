#include "Paket.h"

void Paket::pisi(ostream & os) const {
	os << "[";
	for (int i = 0; i < zbirka_.brojElemenata(); i++) {
		os << *zbirka_[i];
	}
	
	os << "]";
}
