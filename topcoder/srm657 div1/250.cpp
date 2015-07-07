#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class ProblemSets {
public:
	long long maxSets(long long E, long long EM, long long M, long long MH, long long H);
};

bool check(long long E, long long EM, long long M, long long MH, long long H, long long mid) {
	long long t1 = max(0LL, mid - E), t2 = max(0LL, mid - H);
	return EM >= t1 && MH >= t2 && EM - t1 + MH - t2 + M >= mid;
}

long long ProblemSets :: maxSets(long long E, long long EM, long long M, long long MH, long long H) {
	long long l = 0, r = E + EM;
	while (l != r) {
		long long mid = (l + r + 1) / 2;
		if (check(E, EM, M, MH, H, mid)) l = mid;
		else r = mid - 1;
	}
	return l;
}

