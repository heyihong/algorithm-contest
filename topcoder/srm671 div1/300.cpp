#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

const int N(205), MOD(1000000007);

void add(int & val, int inc) {
	val = (val + inc) % MOD;
}

inline int mul(int x, int y) {
	return (long long) x * y % MOD;
}

class BearCries {
public:
	int count(string message);
};

int f[N][N][N];

int BearCries :: count(string message) {
	f[0][0][0] = 1;	
	int n = message.size();	
	for (int i = 0; i != n; ++i) {
		for (int j = 0; j <= i; ++j) {
			for (int k = 0; k <= j; ++k) {
				if (f[i][j][k]) {
					if (message[i] == ';') {
						add(f[i + 1][j + 1][k + 1], f[i][j][k]);		
						if (j > k) {
							add(f[i + 1][j - 1][k], mul(f[i][j][k], j - k));	
						}
					} else if (j > 0) {
						if (k) {
							add(f[i + 1][j][k - 1], mul(f[i][j][k], k));	
						}
						add(f[i + 1][j][k], mul(f[i][j][k], j - k));
					}	
				}	
			}		
		}
	}
	return f[n][0][0];
}
