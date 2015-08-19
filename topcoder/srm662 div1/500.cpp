#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

class ExactTree {
public:
	int getTree(int n, int m, int r);
};

void update(int &v, int nv) {
	if (v == -1 || v > nv) 
		v = nv;
}

int ExactTree :: getTree(int n, int m, int r) {
	int dp[n + 1][m];
	memset(dp, -1, sizeof(dp));
	dp[1][0] = 0;
	for (int i = 2; i <= n; ++i) 
		for (int j = 0; j != m; ++j) 
			for (int x = 1; x <= i - 1; ++x) 
				for (int y = 0; y != m; ++y) {
					if (dp[x][y] == -1 || dp[i - x][j] == -1) {
						continue;
					}
					int count = dp[x][y] + dp[i - x][j] + x * (n - x);
					update(dp[i][count % m], count);
				}
	return dp[n][r];
}

