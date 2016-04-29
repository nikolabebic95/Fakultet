#include <iostream>
#include "Predmet.h"
#include "Tegla.h"
#include "Kutija.h"
#include "Polica.h"
#include "Izuzeci.h"

using namespace std;

int main(void) {
	cout << "Dobrodosli" << endl;
	Polica<Predmet*> p(5, 50);

	while (true) {
		try {
			int izbor;
			cout << "1 - Procitaj predmet i stavi na policu" << endl;
			cout << "2 - Uzmi predmet sa procitanog mesta i ispisi" << endl;
			cout << "3 - Ispisi policu" << endl;
			cout << "0 - Zavrsi program" << endl;
			cin >> izbor;
			if (izbor == 1) {
				Predmet *stvar;
				cout << "Unesite tezinu predmeta: ";
				double tezina;
				cin >> tezina;
				cout << "1 - Tegla" << endl;
				cout << "2 - Kutija" << endl;
				int izborPredmeta;
				cin >> izborPredmeta;
				if (izborPredmeta == 1) {
					cout << "Unesite poluprecnik i visinu tegle: ";
					double poluprecnik, visina;
					cin >> poluprecnik >> visina;
					stvar = new Tegla(poluprecnik, visina);
				}
				else {
					cout << "Unesite stranice a, b i c: ";
					double a, b, c;
					cin >> a >> b >> c;
					stvar = new Kutija(a, b, c);
				}
				stvar->setTezina(tezina);
				p += stvar;
			}
			else if (izbor == 2) {
				Predmet *stvar;
				int x;
				cout << "Unesite mesto sa kog zelite da uzmete predmet: ";
				cin >> x;
				stvar = p.uzmi(x);
				if (stvar != nullptr) cout << *stvar << endl;
				else cout << "Na tom mestu nije bilo nista" << endl;
			}
			else if (izbor == 3) cout << p << endl;
			else if (izbor == 0) exit(0);
		}
		catch (NemaMesta &n) {
			cout << n.what() << endl;
		}
		catch (Preopterecenje &p) {
			cout << p.what() << endl;
		}
		catch (LosIndeks &l) {
			cout << l.what() << endl;
		}
		catch (exception &e) {
			cout << e.what() << endl;
			exit(-1);
		}
		catch (...) {
			cout << "Neidentifikovan izuzetak" << endl;
			exit(-1);
		}//trebalo bi da je nepotrebna grana, ali ko zna :D
	}
	return 0; //da ne skidaju poene, iako nikad nece doci do ovoga
}
