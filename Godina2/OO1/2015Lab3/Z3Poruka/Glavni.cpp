#include <iostream>
#include "Zbirka.h"
#include "Izuzeci.h"
#include "Poruka.h"
#include "Posiljalac.h"
#include "Tekstualna.h"
#include "Brojcana.h"
#include <exception>
#include <conio.h>

using namespace std;

int main(void) {
	try {
		int broj;
		cout << "Unesite koliko parova zelite da unesete: ";
		cin >> broj;
		Zbirka<Posiljalac*, Poruka*> sanduce(broj);
		for (int i = 0; i < broj; i++) {
			Posiljalac *pos;
			string ime;
			cout << "Unesite ime " << i + 1 << ". posiljaoca: ";
			cin >> ime;
			pos = new Posiljalac(ime);
			Poruka *por;
			cout << "1 - Tekstualna poruka" << endl;
			cout << "2 - Brojcana poruka" << endl;
			int izbor;
			cin >> izbor;
			if (izbor == 1) {
				string tekst;
				cout << "Unesite poruku u jednoj liniji:" << endl;
				cin.ignore();
				getline(cin, tekst);
				por = new Tekstualna(tekst);
			}
			else {
				int broj;
				cout << "Unesite broj: ";
				cin >> broj;
				por = new Brojcana(broj);
			}
			try {
				sanduce.dodaj(pos, por);
			}
			catch (VecPostoji &v) {
				cout << v.what() << endl;
				i--;
			}
		}
		cout << "Unesite koliko poruka zelite da ispisete: ";
		cin >> broj;
		for (int i = 0; i < broj; i++) {
			string ime;
			cout << "Unesite ime posiljaoca ciju poruku zelite da ispisete: ";
			cin >> ime;
			Posiljalac p(ime);
			try {
				cout << "Poruka: " << sanduce[p] << endl;
			}
			catch (NePostoji &n) {
				cout << n.what() << endl;
			}
		}
		
	}
	catch (exception &e) {
		cout << e.what() << endl;
		exit(-1);
	}

	cout << "Pritisnite bilo sta za prekid";
	_getch();
	return 0;
}