#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN(20);

double p[MAXN];
double pro[MAXN];
double f[MAXN][MAXN];

int main() {
	int test_cases;
	int n, k;
	scanf("%d", &test_cases);
	for (int tc = 1; tc <= test_cases; ++tc) {
		scanf("%d%d", &n, &k);	
		for (int i = 0; i != n; ++i) {
			scanf("%lf", &p[i]);	
		}
		double ans = 0;
		for (int i = 0; i != (1 << n); ++i) {
			int t = 0;
			for (int j = 0; j != n; ++j) {
				if (i & (1 << j)) {
					pro[t++] = p[j];
				}	
			}
			if (t != k) {
				continue;
			}
			memset(f, 0, sizeof(f));	
			f[0][0] = 1;
			for (int j = 0; j != k; ++j) {
				for (int l = 0; l <= j; ++l) {
					f[j + 1][l] += f[j][l] * (1 - pro[j]);
					f[j + 1][l + 1] += f[j][l] * pro[j];
				}	
			} 
			ans = max(ans, f[k][k / 2]);
		}
		printf("Case #%d: %.8lf\n", tc, ans);
	}
	return 0;	
}