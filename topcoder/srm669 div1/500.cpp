#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

const int MOD(1000000007);

inline int add(int x, int y) {
	return (x + y) % MOD;	
}

inline int mul(int x, int y) {
	return (long long) x * y % MOD;	
}

int pow(int a, int b) {
	if (b == 0) {
		return 1;
	}	
	int t = pow(a, b / 2);
	t = mul(t, t);
	return b % 2 ? mul(t, a) : t;
}

class LineMST {
public:
	int count(int N, int L);	
};

int LineMST :: count(int N, int L) {
	vector<vector<int>> dp = vector<vector<int>>(N + 1, vector<int>(L + 1, 0));
	vector<vector<int>> sum_dp = vector<vector<int>>(N + 1, vector<int>(L + 1, 0));
	dp[1][0] = 1;
	for (int i = 2; i <= N; ++i) {
		sum_dp[i - 1][0] = dp[i - 1][0];
		for (int j = 1; j <= L; ++j) {
			sum_dp[i - 1][j] = add(sum_dp[i - 1][j - 1], dp[i - 1][j]);
		}
		for (int j = 1; j <= L; ++j) {
			for (int k = 1; k < i; ++k) {
				int num_edges = (k * (i - k) - 1);
				int num_weighted_edges = pow(L - j + 1, num_edges);
				dp[i][j] = add(dp[i][j], mul(mul(sum_dp[k][j - 1], sum_dp[i - k][j]), num_weighted_edges));	
			}
		}	
	}
	int ans = 0;
	for (int i = 1; i <= L; ++i) {
		ans = add(ans, dp[N][i]);
	}	
	cout << ans << endl;
	int div2 = pow(2, MOD - 2);	
	for (int i = 1; i <= N; ++i) {
		ans = mul(ans, i);
	}
	ans = mul(ans, div2);	
	return ans;
}