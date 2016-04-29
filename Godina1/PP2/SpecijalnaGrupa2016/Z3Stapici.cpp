#include <iostream>
#include <algorithm>
#include <conio.h>

using namespace std;

bool cmp(const int &lhs, const int &rhs) {
	return lhs > rhs;
}

int sticks[1000000];

int main(void) {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) cin >> sticks[i];
	sort(sticks, sticks + n, cmp);
	int j = 0;
	for (int i = 0; i < n - 1; i++) {
		if (sticks[i] == sticks[i + 1] + 1) sticks[i]--;
		if (sticks[i] == sticks[i + 1]) sticks[j++] = sticks[i++];
	}
	n = j;
	unsigned long long area = 0;
	for (int i = 0; i < n - 1; i += 2) area += (unsigned long long)sticks[i] * sticks[i + 1];
	cout << area << endl;
	cout << "Pritisnite bilo sta za izlaz" << endl;
	while (!_kbhit());
}

