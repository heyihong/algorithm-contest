#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstring>

using namespace std;

const int N(105);

class DancingForever {
public:
	vector <int> getStablePairs(string x);	
};

int n;
bool g[N][N];
int l[N];
bool c[N];

bool find(int x) {
	for (int i = 0; i != n; ++i)
		if (!c[i] && g[x][i]) {
			c[i] = true;
			if (l[i] == -1 || find(l[i])) {
				l[i] = x;
				return true;
			}
		}
	return false;
}

vector <int> DancingForever :: getStablePairs(string x) {
	n = (int)sqrt((double)x.size() + 1e-6);
	for (int i = 0; i != n; ++i)
		for (int j = 0; j != n; ++j)
			g[i][j] = x[i * n + j] == 'Y';
	memset(l, -1, sizeof(l));
	for (int i = 0; i != n; ++i) {
		memset(c, false, sizeof(c));
		if (!find(i)) {
			break;
		}
		memset(c, true, sizeof(c));
	}
	vector<int> ans;
	for (int i = 0; i != n; ++i) 
		if (c[i]) {
			ans.push_back(l[i]);
			ans.push_back(i);
		}
	return ans;
}
