#include <iostream>

#include "Otpornik.h"
#include "Prost.h"
#include "Slozen.h"
#include "Redna.h"
#include <conio.h>

using namespace std;

int main(void) {
	Redna r1(3);
	Redna r2(2);
	Prost p1(5), p2(3), p3(2), p4, p5(42);

	Slozen *s = &r2;

	*s += &p1;
	*s += &p2;
	s = &r1;
	*s += &r2;
	*s += &p3;
	*s += &p4;
	*s += &p5;

	cout << r1 << endl << "Pritisnite bilo sta za prekid programa..." << endl;

	_getch();

}

