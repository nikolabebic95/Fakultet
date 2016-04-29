#include <iostream>

#include "Kvadar.h"
#include "Lista.h"
#include "Skup.h"

using namespace std;

int main(void) {
	while (true) {
		cout << "Unesite broj clanova liste (0 za prekid): ";
		int n;
		cin >> n;
		if (n == 0) exit(0);
		Lista l;
		Skup s;
		for (int i = 0; i < n; i++) {
			cout << "Unesite stranice " << i + 1 << ". kvadra: ";
			int a, b, c;
			cin >> a >> b >> c;
			Kvadar *k1 = new Kvadar(a, b, c);
			Kvadar *k2 = new Kvadar(*k1);
			l += k1;
			s += k2;
		}
		cout << "Lista: " << l << endl;
		cout << "Skup: " << s << endl;
	}
}
