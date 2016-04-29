#include <iostream> 

#include "Tacka.h"
#include "Ponderisana.h"
#include "Mnogougao.h"

using namespace std;


int main(void) {
	while (true) {
		int n;
		cout << "Unesite broj temena: ";
		cin >> n;
		if (n <= 0) exit(0);
		Mnogougao m(n);
		for (int i = 0; i < n; i++) {
			cout << "Unesite 0 ako je teme obicna tacka, a bilo sta drugo ako je ponderisana: ";
			int kakva;
			cin >> kakva;
			Tacka *t;
			cout << "Unesite tacku: ";
			if (kakva == 0) {
				double x, y, z;
				cin >> x >> y >> z;
				t = new Tacka(x, y, z);
			}
			else {
				double x, y, z, q;
				cin >> x >> y >> z >> q;
				t = new Ponderisana(x, y, z, q);
			}
			m += t;
		}
		cout << endl << endl << "Mnogougao je " << m << endl;
		cout << "Najbliza tacka je " << *m.nadjiNajblize() << endl;
	}
}

