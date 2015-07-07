#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <cstring>

using namespace std;

const int N(55);

class Privateparty {
public:
	double getexp(vector <int> a);
};

bool bo[N];

double Privateparty :: getexp(vector <int> a) {
	int n = a.size();
	double ans = 0;
	for (int i = 0; i != n; ++i) {
		memset(bo, false, sizeof(bo));
		double p = 1;
		int cnt = 2;
		for (int j = i; !bo[j]; j = a[j]) {
			bo[j] = true;
			if (cnt % 2 == 0) {
				if (bo[a[j]]) ans += p;
				else ans += p * (1 - 1 / (double)cnt);
			}
			p /= (double)cnt;
			++cnt;
		}
	}
	return ans;
}
