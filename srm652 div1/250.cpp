
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

using namespace std;

const int MAXN(100010), MOD(1000000007);

bool bo[MAXN];

class ThePermutationGame {
public:
	int findMin(int N);
};

inline int mul(int x, int y) {
	return (long long) x * y % MOD;
}

int ThePermutationGame :: findMin(int N) {
	int res = 1;	
	for (int i = 2; i <= N; ++i) {
		if (bo[i]) continue;
		for (int j = 2 * i; j <= N; j += i)
			bo[j] = true;
		int t = 1;
		for (; (long long) t * i <= N; t *= i);
		res = mul(res, t);
	}
	return res;
}

