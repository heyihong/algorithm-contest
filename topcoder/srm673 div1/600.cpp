#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

const int MAXN(105), MAXS(105);

class BearPermutations {
public:
	int countPermutations(int N, int S, int MOD);
};


int f[MAXN][MAXN + MAXS][3];
int comb[MAXN][MAXN];

inline int mul(int a, int b, int MOD) {
	return (long long)a * b % MOD;
}

inline int add(int a, int b, int MOD) {
	return  (a + b) % MOD;
}

void update(int siz, int sum, int root, int cnt, int MOD) {
	f[siz][sum][0] = add(f[siz][sum][0], cnt, MOD);
	f[siz][sum + siz + 1 - root][1] = add(f[siz][sum + siz + 1 - root][1], cnt, MOD);
	f[siz][sum + root][2] = add(f[siz][sum + root][2], cnt, MOD);
}

int BearPermutations :: countPermutations(int N, int S, int MOD) {
	for (int i = 0; i <= N; ++i) {
		comb[i][0] = 1;
		for (int j = 1; j <= i; ++j) {
			comb[i][j] = add(comb[i - 1][j - 1], comb[i - 1][j], MOD);
		}
	}
	f[1][0][0] = f[1][0][2] = 1;
	f[1][2][1] = 1;
	for (int i = 2; i <= N; ++i) {
		for (int j = 0; j != i; ++j) {
			if (j == 0) {
				for (int rs = 0; rs <= S; ++rs) {
					if (f[i - 1][rs][0]) {
						update(i, rs, j, f[i - 1][rs][0], MOD);	
					}
				}
			} else if (j == i - 1) {
				for (int ls = 0; ls <= S; ++ls) {
					if (f[i - 1][ls][0]) {
						update(i, ls, j, f[i - 1][ls][0], MOD);
					}
				}
			} else {
				for (int ls = 0; ls <= S + j + 1; ++ls)  {
					for (int rs = 0; rs < S + i - 1 - j; ++rs) {
						int sum = ls + rs;
						int cnt = mul(mul(f[j][ls][1], f[i - 1 - j][rs][2], MOD), comb[i - 1][j], MOD);
						if (sum <= S && cnt) {
							update(i, sum, j, cnt, MOD);
						}
					}
				}	
			}
		}
	}
	int ans = 0;
	for (int i = 0; i <= S; ++i) {
		ans = add(ans, f[N][i][0], MOD);
	}
	return ans;
}
