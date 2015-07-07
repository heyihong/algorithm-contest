#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

const int MAXN(1000010), MAXK(2505), MOD(1000000007);

class PermutationCounts {
public:
	int countPermutations(int N, vector<int> pos);
};

int fact[MAXN];
int f[MAXK];

inline int mul(int a, int b) {
	return (long long) a * b % MOD;
}

inline int add(int a, int b) {
	return (a + b) % MOD;
}

int pow(int a, int b) {
	if (b == 0) return 1;
	int t = pow(a, b / 2);
	t = mul(t, t);
	return b % 2 ? mul(t, a) : t;
}

int inv(int a) {
	return pow(a, MOD - 2);
}

int PermutationCounts :: countPermutations(int N, vector<int> pos) {
	pos.push_back(0);
	sort(pos.begin(), pos.end());
	pos.push_back(N);
	int K = pos.size();
	fact[0] = 1;
	for (int i = 1; i <= N; ++i)
		fact[i] = mul(fact[i - 1], i);
	f[0] = 1;
	for (int i = 1; i != K; ++i) {
		for (int j = 0; j != i; ++j) {
			f[i] = (mul(f[j], inv(fact[pos[i] - pos[j]])) + MOD - f[i]) % MOD;
		}
	}
	return mul(fact[N], f[K - 1]);
}