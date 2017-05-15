#include "Skladiste.h"
#include <iostream>
#include "Cigla.h"

using namespace std;

int main() {
	try {
		Skladiste s;
		Cigla cigla(0, 0, 0, 0);
		Proizvod *p = nullptr;

		while (true) {
			cout << "1. Procitaj proizvod" << endl;
			cout << "2. Izvadi proizvod" << endl;
			cout << "3. Ispisi skladiste" << endl;
			cout << "0. Zavrsi program" << endl;

			int izbor;
			cin >> izbor;
			switch (izbor) {
			case 1:
				int cena, a, b, c;
				cin >> cena >> a >> b >> c;
				cigla = Cigla(cena, a, b, c);
				s += &cigla;
				break;
			case 2:
				p = s.uzmi();
				cout << *p << endl;
				delete p;
				break;
			case 3:
				cout << s << endl;
				break;
			case 0:
				exit(0);
			default:
				break;
			}
		}
	}
	catch (exception &e) {
		cout << e.what() << endl;
	}
}
