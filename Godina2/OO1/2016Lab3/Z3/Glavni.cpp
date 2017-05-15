#include <iostream>
#include "Racun.h"

using namespace std;

int main() {
	cout << "Broj stavki: ";
	int broj;
	cin >> broj;
	
	Racun r("Racun", 11012017, broj);
	
	for (int i = 0; i < broj; i++) {
		cout << i + 1 << ". stavka: ";
		string naziv;
		double cena;
		int kolicina;
		cin >> naziv >> cena >> kolicina;
		Stavka s(naziv, cena, kolicina);
		r += &s;
	}

	cout << r << endl;
}