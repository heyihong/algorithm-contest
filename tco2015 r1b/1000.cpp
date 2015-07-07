#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

const int N(2010), MOD(1000000007);

class TheTreeAndMan {
public:
	int solve(vector <int> parent);
};

vector<int> childs[N];
int ans;
int c2[N], size[N];

inline int add(int x, int y) {
	return (x + y) % MOD;
}

inline int mul(int x, int y) {
	return (long long) x * y % MOD;
}

inline int cn2(int s) {
	return s * (s - 1) / 2;
}

void dfs(int x, int d) {
	size[x] = 1;
	int tmp = 0;
	for (int y : childs[x]) {
		dfs(y, d + 1);
		size[x] += size[y];
		tmp -= cn2(size[y]);
		c2[x] = add(c2[x], c2[y]);
	}
	tmp += cn2(size[x] - 1);
	c2[x] = add(c2[x], tmp);
	//cout << x << " " << c2[x] << " " << tmp << endl;
	for (int y : childs[x]) {
		tmp = cn2(size[x] - 1 - size[y]);
		for (int z : childs[x])
			if (y != z) {
				tmp -= cn2(size[z]);
			}
		ans = add(ans, mul(d, mul(tmp, c2[y])));
	}
}

int TheTreeAndMan :: solve(vector <int> parent) {
	for (int i = 1; i <= parent.size(); ++i) {
		childs[parent[i - 1]].push_back(i);
	}
	dfs(0, 0);
	return ans;
}

