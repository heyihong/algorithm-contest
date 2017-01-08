#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN(10);

string str[MAXN];
int fa[MAXN];
int a[MAXN];
int b[MAXN];
pair<int, int> pa[MAXN];
int f[1 << MAXN];
int co[1 << MAXN];

int find(int x) {
	return fa[x] != -1 ? find(fa[x]) : x;
}

void merge(int x, int y) {
	x = find(x);
	y = find(y);	
	if (x != y) {
		fa[x] = y;	
	}
}

int main() {
	int test_cases;
	cin >> test_cases;
	for (int tc = 1; tc <= test_cases; ++tc) {
		int n;
		cin >> n;
		int cost = 0;
		for (int i = 0; i != n; ++i) {
			cin >> str[i];
			for (int j = 0; j != n; ++j) {
				if (str[i][j] == '1') {
					cost -= 1;	
				}	
			}
		}
		memset(fa, -1, sizeof(fa));
		int cnt = 0;
		for (int i = 0; i != n; ++i) {
			int p = -1;
			for (int j = 0; j != n; ++j) {
				if (str[j][i] == '1') {
					if (p != -1) {
						merge(p, j);
					}
					p = j;	
				}	
			}	
			if (p == -1) {
				cnt++;
			}
		}	
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		for (int i = 0; i != n; ++i) {
			if (i != find(i)) {
				for (int j = 0; j != n; ++j) {
					if (str[i][j] == '1') {
						str[find(i)][j] = '1';
					}
				}	
			}
			a[find(i)]++;
		}		
		for (int i = 0; i != n; ++i) {
			if (i == find(i)) {
				for (int j = 0; j!= n; ++j) {
					if (str[i][j] == '1') {
						b[i] += 1;
					}
				}
			}
		}
		int t = 0;
		for (int i = 0; i != n; ++i) {
			if (i == find(i)) {
				if (a[i] != b[i]) {
					pa[t++] = make_pair(a[i], b[i]);	
				} else {
					cost += a[i] * b[i];
				}
			}
		}
		memset(co, -1, sizeof(co));
		for (int i = 0; i != (1 << t); ++i) {
			int ta = 0, tb = 0;
			for (int j = 0; j != t; ++j) {
				if (i & (1 << j)) {
					ta += pa[j].first;
					tb = max(tb, pa[j].second);
				}	
			}		
			if (ta >= tb) {
				co[i] = ta * ta;
			}
		}
		memset(f, -1, sizeof(f));	
		f[0] = 0;
		for (int i = 0; i != (1 << t); ++i) {
			if (f[i] == -1) {
				continue;
			}
			int st = ((1 << t) - 1) ^ i;
			for (int j = st; j; j = (j - 1) & st) {
				if (co[j] != -1) {
					if (f[i ^ j] == -1 || f[i ^ j] > f[i] + co[j]) {
						f[i ^ j] = f[i] + co[j];
					}
				}	
			}
		}
		cout << "Case #" << tc << ": " << cost + f[(1 << t) - 1] << endl;
	}
	return 0;	
}