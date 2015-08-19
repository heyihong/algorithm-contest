#include <iostream>

using namespace std;

const int MAXM(1000010);

class ColorfulLineGraphs {
public:
	int countWays(long long N, long long K, int M);
};

int mod;
int mult[MAXM];

int mul(int a, int b) {
	return (long long)a * b % mod;
}

int add(int a, int b) {
	return (a + b) % mod;
}

int pow(int a, long long b) {
	if (b == 0) {
		return 1;
	}
	int t = pow(a, b / 2);
	t = mul(t, t);
	return b % 2 ? mul(t, a) : t;
}

int ColorfulLineGraphs :: countWays(long long N, long long K, int M) {
	mod = M;
	int t = (K - 1) % M;
	mult[0] = 1;
	for (int i = 1; i <= M; ++i) {
		mult[i] = mul(mult[i - 1], add(mul(t, i), 1));
	}
	return mul(pow(mult[M], N / M), mult[N % M]);
}

