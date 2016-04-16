#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int N(55), INF(1 << 20);

class Treestrat {
public:
	int roundcnt(vector <int> tree, vector <int> A, vector <int> B);
};

int n;
int g[N][N];

int Go(int f, int t) {
	if (f == t) {
		return t;
	}	
	for (int i = 0; i != n; ++i) {
		if (g[f][i] == 1 && g[f][i] + g[i][t] == g[f][t]) {
			return i;
		}
	}
	return -1;
}

int Catch(int red, vector<int> blues) {
	int result = 0;
	for (int d = 0; d != n; ++d) {
		int r = red;
		vector<int> bs = blues;
		for (int num_rounds = 1; ; ++num_rounds) {
			r = Go(r, d);		
			bool flag = false;
			for (int i = 0; i != blues.size(); ++i) {
				bs[i] = Go(bs[i], r);
				if (bs[i] == r) {
					flag = true;
					break;
				}
			}		
			if (flag) {
				result = max(result, num_rounds);
				break;
			}	
		}
	}	
	return result;
}

int Treestrat :: roundcnt(vector <int> tree, vector <int> A, vector <int> B) {
	n = tree.size() + 1;
	for (int i = 0; i != n; ++i) {
		for (int j = 0; j != n; ++j) {
			if (i != j) {
				g[i][j] = INF;
			}
		}
	}
	for (int i = 0; i != tree.size(); ++i) {
		g[tree[i]][i + 1] = g[i + 1][tree[i]] = 1;
	}	
	for (int k = 0; k != n; ++k) {
		for (int i = 0; i != n; ++i) {
			for (int j = 0; j != n; ++j) {
				g[i][j] = min(g[i][j], g[i][k] + g[k][j]);	
			}
		}
	}
	int result = INF;		
	for (int a : A) {
		result = min(result, Catch(a, B));
	}	
	return result;
}