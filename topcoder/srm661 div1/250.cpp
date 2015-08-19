#include <iostream>

using namespace std;

const int MAXN(1000010);

class MissingLCM {
public:
	int getMin(int N);
};

bool bo[MAXN];

int MissingLCM :: getMin(int N) {
	memset(bo, false, sizeof(bo));
	int m = N + 1;
	for (int i = 2; i <= N; ++i) {
		if (!bo[i]) {
			for (int j = 2 * i; j <= N; j += i)
				bo[j] = true;
			int p = i;
			for (;p <= N / i; p *= i);
			m = max(m, (N + p - 1) / p * p);
		}
	}
	return m;
}
