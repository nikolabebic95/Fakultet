#include <iostream>

using namespace std;

#include "Tacka.h"
#include "Merenje.h"
#include "MernaTacka.h"
#include "Zbirka.h"
#include <conio.h>

int main(void) {
	Merenje m1(20, 2880000), m2(25, 4320000), m3(30, 5400000), m4(25, 6480000), m5(20, 7920000), m6(25, 4320000);

	Merenje *niz1[4] = { &m1, &m2, &m3, &m4 };
	Merenje *niz2[2] = { &m5, &m6 };

	MernaTacka t1(4, niz1, 5, 5, 5);
	MernaTacka t2(2, niz2, 0, 0, 0);

	Zbirka z(5);

	z += &t1;
	z += &t2;

	cout << "Prosecna temperatura izmedju 11 i 19 sati je: " << z(3960000, 6840000) << endl;
	cout << "Za kraj programa pritisnite bilo sta..." << endl;
	_getch();
}