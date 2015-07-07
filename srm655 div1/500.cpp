#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

const int N(5), M(5010), S(9 * 9 * 9 * 9 * 9), MOD(1000000007);

class Nine {
public:
	int count(int n, vector <int> d);
};

int p9[N + 1];
int f[M][9];
int cnt[1 << N];
int ans[S], _ans[S];
int num[N];

int mul(int a, int b) {
	return (long long)a * b % MOD;
}

int Nine :: count(int n, vector <int> d) {
	p9[0] = 1;
	for (int i = 1; i <= N; ++i) {
		p9[i] = p9[i - 1] * 9;
	}
	f[0][0] = 1;
	for (int i = 0; i < d.size(); ++i) 
		for (int j = 0; j != 9; ++j) {
			if (f[i][j] > 0) {
				for (int k = 0; k != 10; ++k)
					f[i + 1][(j + k) % 9] = (f[i + 1][(j + k) % 9] + f[i][j]) % MOD;
			}
		}
	for (int digit : d) {
		++cnt[digit];
	}
	ans[0] = 1;
	for (int trans = 0; trans < (1 << n); ++trans) {
		if (cnt[trans] == 0) 
			continue;
		memset(_ans, 0, sizeof(_ans));
		for (int stat = 0; stat < p9[n]; ++stat) {
			if (!ans[stat])
				continue;
			for (int ord = 0; ord != n; ++ord)
				num[ord] = stat / p9[ord] % 9;
			for (int dig = 0; dig < 9; ++dig) {
				int nstat = 0;
				for (int ord = n - 1; ord >= 0; --ord) {
					nstat = nstat * 9;
					if (trans & (1 << ord)) {
						nstat += (num[ord] + dig) % 9;
					}
					else nstat += num[ord];
				}
				_ans[nstat] = (_ans[nstat] + mul(ans[stat], f[cnt[trans]][dig])) % MOD;
			}
		}
		memcpy(ans, _ans, sizeof(_ans));
	}
	return ans[0];
}