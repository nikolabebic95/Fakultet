/* Tekst zadatka - http://rti.etf.bg.ac.rs/rti/ir1pp2/postavke/SI1PP2_DZ1_2016_Spec_grupa.pdf */

#include <iostream>
#include <algorithm>
#include <conio.h>

using namespace std;

struct Range {
	int index;
	double left;
	double right;
};

bool cmp(const Range &lhs, const Range &rhs) {
	if (lhs.left < rhs.left) return true;
	if (lhs.left > rhs.left) return false;
	if (lhs.right <= rhs.right) return true;
	return false;
}

int main(void) {
	Range tunnel;
	cin >> tunnel.left >> tunnel.right;
	int n;
	cin >> n;
	Range lamps[20000];
	for (int i = 0; i < n; i++) {
		lamps[i].index = i;
		cin >> lamps[i].left >> lamps[i].right;
	}
	sort(lamps, lamps + n, cmp);
	bool possible = false;
	int solution[20000];
	int counter = 0;
	double left = tunnel.left;
	double right = tunnel.left;
	if (lamps[0].left <= tunnel.left) {
		for (int i = 0; i < n; i++) {
			if (counter == 0) {
				solution[counter] = i;
				left = tunnel.left;
				right = lamps[i].right;
				if (right<tunnel.left) right = tunnel.left;
				counter++;
			}
			else if (lamps[i].left>right) {
				possible = false;
				break;
			}
			else if (lamps[i].right <= right) continue;
			else if (lamps[i].left < left) {
				solution[counter - 1] = i;
				right = lamps[i].right;
			}
			else {
				solution[counter] = i;
				left = right;
				right = lamps[i].right;
				counter++;
			}
			if (right >= tunnel.right) {
				possible = true;
				break;
			}
		}
	}
	if (possible) {
		cout << counter << endl;
		for (int i = 0; i < counter; i++) cout << lamps[solution[i]].index << " ";
		cout << endl;
	}
	else cout << "Nemoguce" << endl;
	cout << "Pritisnite bilo sta za izlaz" << endl;
	while (! _kbhit());
}

