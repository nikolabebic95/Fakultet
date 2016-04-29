#ifndef _kupac_h_
#define _kupac_h_

#include "Akter.h"
#include "Prodavnica.h"
#include "Izuzeci.h"

template <typename T> class Kupac : public Akter<T> {
public:
	void radnja(Prodavnica<T> &p) const override {
		cout << *this << " ";
		try {
			T t = p.uzmi();
			cout << t;
		}
		catch (NemaNista &n) {
			cout << n.what();
		}
		cout << endl;
	}
};

#endif