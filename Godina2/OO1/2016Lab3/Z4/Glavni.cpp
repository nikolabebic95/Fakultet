#include <iostream>
#include "Roba.h"
#include "Artikal.h"

using namespace std;

Roba* procitajRobu() {
	cout << "Oznaka i vrednost: (oznaka X za kraj) ";
	
	char oznaka;
	int vrednost;
	
	cin >> oznaka;
	if (oznaka == 'X') {
		return nullptr;
	}

	cin >> vrednost;

	return new Artikal(oznaka, vrednost);
}

int main() {	
	while (true) {
		Roba *roba = procitajRobu();
		
		if (roba == nullptr) {
			break;
		}
		
		cout << *roba << endl;
		delete roba;
	}

	return 0;
}
