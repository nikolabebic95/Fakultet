#include "Stavka.h"
#include "Racun.h"
#include "Zbirka.h"

using namespace std;

int main() {
	Racun racun(5, ":*", 20161130);

	Stavka s1("Mica", 100000, 1);
	Stavka s2("Ne znam sta jos", 17, 397);

	racun += &s1;
	racun += &s2;

	cout << racun << endl;
}
