#include <iostream>
#include <vector>

using namespace std;

const int MOD(1000000007);

class KitayutaMart {
public:
	int lastPrice(int N, int K);
};

inline int mul(int a, int b) {
	return (long long) a * b % MOD;
}

int pow2(int n) {
	if (n == 0) return 1;
	int t = pow2(n / 2);
	t = mul(t, t);
	if (n % 2) 
		t = mul(t, 2);
	return t;
}

long long total(const vector<int> & cnt, int p) {
	long long ret = 0;
	for (int i = 0; i != cnt.size() && i <= p; ++i)
		ret += (long long)(p - i + 1) * cnt[i];
	return ret;
}

int calc(const vector<int> & cnt, int N) {
	int l = 0, r = 1 << 30;
	while (l != r) {
		int mid = (l + r) / 2;
		if (total(cnt, mid) < N) l = mid + 1;
		else r = mid;
	}
	return l;
}

int calcPrefix(int range, int prefix) {
	if (range < prefix) return 0;
	int ret = 0;
	for (int l = prefix, r = prefix; l <= range; l = l << 1, r = (r << 1) + 1)
		ret += min(r, range) - l + 1;
	return ret;
}

int getNumByRank(int range, int prefix, int rank) {
	if (rank == 1) return prefix;
	--rank;
	int t = calcPrefix(range, prefix << 1);
	if (rank <= t) return getNumByRank(range, prefix << 1, rank);
	return getNumByRank(range, (prefix << 1) + 1, rank - t);
}

int getP(int x) {
	return x == 1 ? 0 : getP(x / 2) + 1;
}

int KitayutaMart :: lastPrice(int N, int K) {
	vector<int> cnt;
	for (int i = 0; (1 << i) <= K; ++i)
		cnt.push_back(min(K + 1, 1 << (i + 1)) - (1 << i));
	int p = calc(cnt, N);
	int range = (p <= 30) && ((K + 1) >> (p + 1)) ? (1 << (p + 1)) - 1 : K;
	int rank = N - total(cnt, p - 1);
	//cout << p << " " << range << " " << rank << endl;
	//[1, range]
	int num = getNumByRank(range, 1, rank);
	return mul(num, pow2(p - getP(num)));
}