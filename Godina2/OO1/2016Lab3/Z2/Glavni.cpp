#include "Disk.h"
#include <iostream>

using namespace std;

int main() {
	try {
		Disk d;

		Imenik &i = d.imenik();

		Imenik i1("Imenik1");
		Imenik i2("Imenik2");

		Datoteka d1("Fajl11", 1024);
		Datoteka d2("Fajl12", 17);

		Datoteka d3("Fajl21", 2048);
		Datoteka d4("Fajl22", 4096);

		i1 += &d1;
		i1 += &d2;

		i2 += &d3;
		i2 += &d4;

		i += &i1;
		i += &i2;

		cout << i << endl;
	}
	catch(exception &e) {
		cout << e.what() << endl;
	}
}
