#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int N(3010), MOD(1000000007);

vector<int> g[N];
bool path[N];
int size[N], cnt[N], fa[N];
int c[N][N], tot[N][N];

class TwoEntrances {
public:
	int count(vector <int> a, vector <int> b, int s1, int s2);
};

int mul(int x, int y) {
	return (long long)x * y % MOD;
}

void travel_tree(int x) {
	size[x] = 1;
	cnt[x] = 1;
	for (int y : g[x])
		if (y != fa[x]) {
			fa[y] = x;
			travel_tree(y);
			size[x] += size[y];
			cnt[x] = mul(cnt[x], mul(c[size[x] - 1][size[y]], cnt[y]));
		}
}

int TwoEntrances :: count(vector <int> a, vector <int> b, int s1, int s2) {
	int n = a.size() + 1;
	for (int i = 0; i <= n; ++i) {
		c[i][0] = 1;
		for (int j = 1; j <= i; ++j)
			c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % MOD;
	}
	for (int i = 0; i != n - 1; ++i) {
		g[a[i]].push_back(b[i]);
		g[b[i]].push_back(a[i]);
	}
	fa[s1] = -1;
	travel_tree(s1);
	vector<int> vec;
	for (int x = s2; x != -1; x = fa[x]) {
		path[x] = true;
		vec.push_back(x);
	}
	for (int x : vec) {
		size[x] = 1;
		cnt[x] = 1;
		for (int y : g[x])
			if (!path[y]) {
				size[x] += size[y];
				cnt[x] = mul(cnt[x], mul(c[size[x] - 1][size[y]], cnt[y]));
			}
	}
	for (size_t i = 0; i != vec.size(); ++i)
		tot[i][i] = cnt[vec[i]];
	for (int i = 1; i != vec.size(); ++i) {
		int win_sum = 0;
		for (int j = 0; j != vec.size(); ++j) {
			win_sum += size[vec[j]];
			if (j >= i) {
				int l = j - i, r = j;
				tot[l][r] = (tot[l][r] + mul(tot[l + 1][r], mul(c[win_sum - 1][size[vec[l]] - 1], cnt[vec[l]]))) % MOD;
				tot[l][r] = (tot[l][r] + mul(tot[l][r - 1], mul(c[win_sum - 1][size[vec[r]] - 1], cnt[vec[r]]))) % MOD;
				win_sum -= size[vec[l]];
			}
		}
	}
	return tot[0][vec.size() - 1];
}