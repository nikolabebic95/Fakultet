#include <iostream>
#include <algorithm>
#include <string>
#include <conio.h>

using namespace std;

bool cmp(const string &lhs, const string &rhs) {
	unsigned n = lhs.length();
	if (rhs.length() < n) n = rhs.length();
	for (unsigned i = 0; i < n; i++) {
		if (lhs[i] < rhs[i]) return false;
		if (lhs[i] > rhs[i]) return true;
	}
	if (lhs.length() == rhs.length()) return true;
	if (lhs.length() < rhs.length()) {
		if (lhs[0] < rhs[n]) return false;
		else return true;
	}
	else {
		if (rhs[0] < lhs[n]) return true;
		else return false;
	}
}

// Test cases have the smallest number
bool cmpSmaller(const string &lhs, const string &rhs) {
	return !cmp(lhs, rhs);
}

int main(void) {
	int n;
	cin >> n;
	string numbers[5000];
	for (int i = 0; i < n; i++) cin >> numbers[i];
	sort(numbers, numbers + n, cmp);
	for (int i = 0; i < n; i++) cout << numbers[i];
	cout << endl;
	cout << "Pritisnite bilo sta za izlaz" << endl;
	while (!_kbhit());
}

