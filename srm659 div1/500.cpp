#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

const int MAXN(16), MAXM(16), MOD(1000000007);

class CampLunch {
public:
	int count(int N, int M, vector <string> a);
};

int f[1 << MAXM], g[1 << MAXM];

inline void add(int & a, int b) {
	a = (a + b) % MOD;
}

int CampLunch :: count(int N, int M, vector <string> a) {
	f[0] = 1;
	for (int i = 0; i != N; ++i) {
		vector<int> pos(M);
		for (int j = 0; j != M; ++j)
			pos[a[i][j] - 'A'] = j;
		for (int j = 0; j != M; ++j) {
			memset(g, 0, sizeof(g));
			for (int k = 0; k != (1 << M); ++k)	{
				if ((k & (1 << j))) {
					add(g[k ^ (1 << j)], f[k]);
					continue;
				}
				add(g[k | (1 << j)], f[k]);
				add(g[k], f[k]); 
				int p = pos[j];
				if (p != M - 1) {
					int nxt = a[i][p + 1] - 'A';
					if ((k & (1 << nxt)) && nxt < j) {
						add(g[k ^ (1 << nxt)], f[k]); 
					}
				}
				if (p > 0) {
					int pre = a[i][p - 1] - 'A';
					if ((k & (1 << pre)) && pre < j) {
						add(g[k ^ (1 << pre)], f[k]);
					}
				}
			}	
			memcpy(f, g, sizeof(g));
		}
	}
	return f[0]; 
}


