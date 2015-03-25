#include <iostream>

using namespace std;

typedef long long LL;

const int SZ(150000), LEN(31);

class XorSequence {
public:
	LL getmax(int N, int sz, int A0, int A1, int P, int Q, int R);
};

int A[SZ];
int trie_size, trie_root;
int trie[SZ * LEN][2];
int cnt[SZ * LEN];
LL pairs[2][LEN];

LL XorSequence :: getmax(int N, int sz, int A0, int A1, int P, int Q, int R) {
	A[0] = A0;
	A[1] = A1;
	for (int i = 2; i < sz; ++i) {
    	A[i] = ((LL)A[i - 2] * P + (LL)A[i - 1] * Q + R) % N;
	}
	trie_size = trie_root = 1;
	for (int i = 0; i < sz; ++i) {
		int p = trie_root;
		++cnt[p];
		for (int j = LEN - 1; j != -1; --j) {
			int bit = (A[i] >> j) & 1;
			pairs[bit][j] += cnt[trie[p][bit ^ 1]];
			if (!trie[p][bit])
			{
				trie[p][bit] = ++trie_size;
			}
			p = trie[p][bit];
			++cnt[p];
		}
	}
	LL ans = 0;
	for (int i = LEN - 1; i != -1; --i)
	{
		ans += max(pairs[0][i], pairs[1][i]);
	}
	return ans;
}
