#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int N(10010), MOD(1000000007);

class PolynomialGCD {
public:
	int gcd(string s);
};

bool bo[N];

inline int mul(int a, int b) {
	return (long long) a * b % MOD;
}

int pow(int a, int b) { 
	if (b == 0) return 1;
	int t = pow(a, b / 2);
	t = mul(t, t);
	return b % 2 ? mul(t, a) : t;
}

int calc(const string & s, int p, int x, int y) {
	if (x + (p - 1) * y >= s.size()) {
		return 0;
	}
	int res = (1LL << 31) - 1;
	for (int i = 0; i != p; ++i, x += y) {
		int tmp = calc(s, p, x, y * p);
		for (int j = x; j < s.size(); j += y * p)
			tmp += s[j] - '0';
		res = min(res, tmp);
	}
	return res;
}

int PolynomialGCD :: gcd(string s) {
	int res = 1;
	for (int i = 2; i <= s.size(); ++i)
		if (!bo[i]) {
			for (int j =2 * i; j <= s.size(); j += i)
				bo[j] = true;
			res = mul(res, pow(i, calc(s, i, 0, 1)));	
		}
	return res;
}

