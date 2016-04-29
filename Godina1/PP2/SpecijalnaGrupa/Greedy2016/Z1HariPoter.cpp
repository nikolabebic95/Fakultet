/* Tekst zadatka - http://rti.etf.bg.ac.rs/rti/ir1pp2/postavke/SI1PP2_DZ1_2016_Spec_grupa.pdf */

#include <iostream>
#include <queue>
#include <string>
#include <conio.h>

using namespace std;

struct cmp {
	bool operator()(const int& lhs, const int& rhs) {
		return lhs > rhs;
	}
};

int main(void) {
	int n, m;
	cin >> n >> m;
	priority_queue<int, vector<int>, cmp> letters[26];
	for (int i = 0; i < n; i++) {
		char c;
		int p;
		cin >> c >> p;
		letters[c - 'A'].push(p);
	}
	string word;
	cin >> word;
	bool possible = true;
	int weight = 0;
	for (int i = 0; i < m; i++) {
		int index = word[i] - 'A';
		if (letters[index].empty()) {
			possible = false;
			break;
		}
		weight += letters[index].top();
		letters[index].pop();
	}
	if (possible) cout << weight << endl;
	else cout << "Nemoguce" << endl;
	cout << "Pritisnite bilo sta za izlaz" << endl;
	while (!_kbhit());
}

