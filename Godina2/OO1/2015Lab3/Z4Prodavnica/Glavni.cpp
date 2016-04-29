#include <iostream>
#include "Prodavnica.h"
#include "Kupac.h"
#include "Proizvod.h"
#include "Izuzeci.h"
#include <conio.h>

using namespace std;

int main(void) {
	try{
		Prodavnica<Proizvod> p(10);
		Kupac<Proizvod> k;
		Proizvod a("Burek", 200);
		Proizvod b("Pica na drva", 100);
		Proizvod c("Big pizza", 150);
		Proizvod d("Rostilj", 1000);
		p += a;
		p += b;
		p += c;
		p += d;
		k.radnja(p);
		k.radnja(p);
	}
	catch (exception &e) {
		cout << e.what();
		exit(-1);
	}
	cout << "Pritisnite bilo sta za izlaz";
	_getch();
	return 0;
}