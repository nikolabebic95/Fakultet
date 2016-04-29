/* Tekst zadatka - http://rti.etf.bg.ac.rs/rti/ir1pp2/postavke/SI1PP2_DZ1_2016_Spec_grupa.pdf */

#include <iostream>
#include <algorithm>
#include <queue>
#include <conio.h>

using namespace std;

struct Station {
	long long position;
	int cost;
};

bool cmp(const Station &lhs, const Station &rhs) {
	return lhs.position < rhs.position;
}

struct Priority {
	bool operator()(const Station &lhs, const Station &rhs) {
		return lhs.cost > rhs.cost;
	}
};

Station stations[200001];

int main(void) {
	long long d, n, m;
	cin >> d >> n >> m;
	for (int i = 0; i < m; i++) cin >> stations[i].position >> stations[i].cost;
	sort(stations, stations + m, cmp);
	priority_queue<Station, vector<Station>, Priority> q;
	int i = 0;
	while (i < m) {
		if (stations[i].position > n) break;
		q.push(stations[i]);
		i++;
	}
	long long reach = n;
	if (reach > d) reach = d;
	long long fuel = 0;
	bool possible = false;
	if (reach == d) possible = true;
	while (!q.empty() && !possible) {
		if (q.empty()) break;
		Station curr = q.top();
		q.pop();
		if (curr.position + n <= reach) continue;
		fuel += (curr.position + n - reach)*curr.cost;
		reach = curr.position + n;
		while (i < m) {
			if (stations[i].position > curr.position + n) break;
			if (stations[i].cost < curr.cost) {
				fuel -= (curr.position + n - stations[i].position)*curr.cost;
				reach = stations[i].position;
				q = priority_queue<Station, vector<Station>, Priority>();
				q.push(stations[i]);
				i++;
				break;
			}
			else {
				q.push(stations[i]);
				i++;
			}
		}
		if (reach >= d) {
			fuel -= (reach - d)*curr.cost;
			possible = true;
			break;
		}
	}
	if (possible) cout << fuel << endl;
	else cout << "Nemoguce" << endl;
	cout << "Pritisnite bilo sta za izlaz" << endl;
	while (!_kbhit());
}

