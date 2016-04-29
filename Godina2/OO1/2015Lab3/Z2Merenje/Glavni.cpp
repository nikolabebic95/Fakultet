#include <iostream>
#include "MernoMesto.h"
#include "MernaOblast.h"
#include <conio.h>

using namespace std;

int main(void) {
	try {
		MernaOblast m(5);
		for (int i = 0; i < 5; i++) {
			MernoMesto x(3);
			for (int j = 0; j < 3; j++) {
				try {
					int vreme;
					double temperatura;
					cout << "Unesite vreme i temperaturu za merenje " << j + 1 << " na mestu " << i + 1 << ": ";
					cin >> vreme >> temperatura;
					Merenje t(vreme, temperatura);
					x += t;
				}
				catch (LoseVreme &v) {
					cout << v.what() << endl;
					j--;
				}
				catch (LosaTemperatura &t) {
					cout << t.what() << endl;
					j--;
				}
			}
			m += x;
		}
		cout << m << endl << m.najmanjaTemperatura();

		cout << endl << endl << "Pritisnite bilo sta za izlaz";
		_getch();
	}
	catch (exception &e) {
		cout << e.what();
		exit(-1);
	}
	return 0;
}