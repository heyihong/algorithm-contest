#include <iostream>
#include <cstring>
#include <string>

using namespace std;

const int MAXN(55), MOD(1000000007);

class Fragile {
public:
	int countGraphs(int N, int K);
};

inline int mul(int x, int y) {
	return (long long) x * y % MOD;
}

inline int add(int x, int y) {
	return (x + y) % MOD;
}

int pow(int a, int b) {
	if (b == 0) return 1;
	int tmp = pow(a, b / 2);
	tmp = mul(tmp, tmp);
	if (b % 2) tmp = mul(tmp, a);
	return tmp;
}

int connected[MAXN], strongConnected[MAXN];
int sumConnected[MAXN][MAXN], connectedWithBridges[MAXN][MAXN], c[MAXN][MAXN], result[MAXN][MAXN];
int sumConnectedWithBridges[MAXN][MAXN][MAXN];

int Fragile :: countGraphs(int N, int K) {
	for (int i = 0; i <= N; ++i) {
		c[i][0] = 1;
		for (int j= 1; j <= i; ++j)
			c[i][j] = add(c[i - 1][j - 1], c[i - 1][j]);
	}
	memset(connected, 0, sizeof(connected));
	for (int i = 0; i <= N; ++i) {
		connected[i] = pow(2, i * (i - 1) / 2);
		for (int j = 1; j < i; ++j) {
			connected[i] = add(connected[i], -mul(mul(c[i - 1][j - 1], connected[j]), pow(2, (i - j) * (i - j - 1) / 2)));
		}
		//cout << "connected[" << i << "] : " << connected[i] << endl;
	}
	memset(sumConnected, 0, sizeof(sumConnected));
	sumConnected[0][0] = 1;
	for (int i = 1; i <= N; ++i) 
		for (int j = 1; j <= i; ++j) {
			for (int k = 1; k <= i; ++k)
				sumConnected[i][j] = add(sumConnected[i][j], 
					mul(sumConnected[i - k][j - 1], mul(mul(c[i - 1][k - 1], connected[k]), k)));
		}
	memset(strongConnected, 0, sizeof(strongConnected));
	for (int i = 0; i <= N; ++i) {
		strongConnected[i] = connected[i];
		for (int j = 1; j <= i; ++j)
			for (int k = 1; k <= i - j; ++k)
				strongConnected[i] = add(strongConnected[i], -mul(mul(c[i - 1][j - 1], strongConnected[j]), mul(pow(j, k), sumConnected[i - j][k])));
		//cout << "strongConnected[" << i << "] : " << strongConnected[i] << endl;
	}
	memset(connectedWithBridges, 0, sizeof(connectedWithBridges));
	connectedWithBridges[0][0] = sumConnectedWithBridges[0][0][0] = 1;
	for (int i = 1; i <= N; ++i) {
		connectedWithBridges[i][0] = strongConnected[i];
		for (int j = 1; j <= i - 1; ++j) { //number of bridges
			for (int k = 1; k <= i; ++k)	 
				for (int l = 0; l <= i - k && l <= j; ++l) //number of connected components
					connectedWithBridges[i][j] = add(connectedWithBridges[i][j], 
						mul(mul(c[i - 1][k - 1], strongConnected[k]), mul(pow(k, l), sumConnectedWithBridges[i - k][j - l][l])));
			//cout << "connectedWithBridges[" << i << "][" << j << "] : " << connectedWithBridges[i][j] << endl;
		}
		for (int j = 0; j <= i - 1; ++j) //number of bridges
			for (int k = 1; k <= i; ++k) { //number of connected components 
				for (int x = 1; x <= i && k - 1 <= i - x; ++x) 
					for (int y = 0; y <= x - 1 && y <= j; ++y)
						sumConnectedWithBridges[i][j][k] = add(sumConnectedWithBridges[i][j][k],
							mul(sumConnectedWithBridges[i - x][j - y][k - 1], mul(x, mul(c[i - 1][x - 1], connectedWithBridges[x][y]))));
			//cout << "sumConnectedWithBridges[" << i << "][" << j << "][" << k << "] : " << sumConnectedWithBridges[i][j][k] << endl;
			}
	}
	memset(result, 0, sizeof(result));
	result[0][0] = 1;
	for (int i = 1; i <= N; ++i) 
		for (int j = 0; j <= i - 1; ++j)
			for (int k = 1; k <= i; ++k)
				for (int l = 0; l <= j; ++l)
					result[i][j] = add(result[i][j], 
						mul(result[i - k][j - l], mul(c[i - 1][k - 1], connectedWithBridges[k][l])));
	return (result[N][K] + MOD) % MOD;
}