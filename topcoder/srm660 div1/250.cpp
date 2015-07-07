#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

const int N(105);

class Coversta {
public:
	int place(vector <string> a, vector <int> x, vector <int> y);
};

int n, m;
vector<int> bx, by;
vector<string> a;
bool bo[N][N];

inline bool inside(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < m;
}

inline int set(int x, int y) {
	if (!inside(x, y) || bo[x][y]) {
		return 0;
	}
	bo[x][y] = true;
	return a[x][y] - '0';
}

inline void reset(int x, int y) {
	if (inside(x, y)) {
		bo[x][y] = false;
	}
}

inline int countValue(int x1, int y1, int x2, int y2) {
	int value = 0;
	for (int i = 0; i != bx.size(); ++i) {
		value += set(x1 + bx[i], y1 + by[i]);
		value += set(x2 + bx[i], y2 + by[i]);
	}
	for (int i =0; i != bx.size(); ++i) {
		reset(x1 + bx[i], y1 + by[i]);
		reset(x2 + bx[i], y2 + by[i]);
	}
	return value;
}

int Coversta :: place(vector <string> _a, vector <int> _x, vector <int> _y) {
	a = _a; bx = _x; by = _y;
	n = a.size(); m = a[0].size();
	vector<pair<int, int> > p;
	for (int i = 0; i != n; ++i)
		for (int j = 0; j != m; ++j) {
			int value = 0;
			for (int k = 0; k != bx.size(); ++k) {
				int tx = i + bx[k], ty = j + by[k];
				if (inside(tx, ty)) {
					value += a[tx][ty] - '0';
				}
			}
			p.push_back(make_pair(value, i * m + j));	
		}
	sort(p.rbegin(), p.rend());
	int maxval = 0;
	for (int i = 0; i != p.size(); ++i) {
		int tx = p[i].second / m, ty = p[i].second % m;
		for (int j = 0; j != bx.size() * bx.size() + 2 && j != p.size(); ++j) {
			int ttx = p[j].second / m, tty = p[j].second % m;
			maxval = max(maxval, countValue(tx, ty, ttx, tty));
		}
	}
	return maxval;
}

