#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int N(255);

class RandomPancakeStack {
public:
	double expectedDeliciousness(vector <int> d);
};

double p[N][N];

double RandomPancakeStack :: expectedDeliciousness(vector <int> d) {
	int n = d.size();
	p[0][0] = 1;
	double ans = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= i; ++j) {
			for (int k = 0; k != i; ++k)
				p[i][j] += p[k][j - 1] / (double)(n - j + 1);
			ans += p[i][j] * d[n - i];
		}
	}
	return ans;
}