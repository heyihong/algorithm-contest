#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class OddEvenTree {
public:
	vector <int> getTree(vector <string> x);
};

int find(vector<int> & fa, int x) {
	return fa[x] == 0 ? x : fa[x] = find(fa, fa[x]);
}

vector <int> OddEvenTree :: getTree(vector <string> x) {
	int n = x.size();
	vector<int> nosol(1, -1);
	vector<vector<int> > g(n, vector<int>(n));
	for (int i = 0; i != n; ++i)
		for (int j = 0; j != n; ++j) {
			g[i][j] = x[i][j] == 'O';
			if (i == j && g[i][j] == 'O')
				return nosol; 
		}
	for (int i = 0; i != n; ++i)
		for (int j = 0; j != n; ++j)
			for (int k = 0; k != n; ++k)
				if (g[j][k] != (g[j][i] ^ g[i][k])) return nosol;
	vector<int> fa(n);
	vector<int> ans;
	for (int i = 0; i != n; ++i)
		for (int j = 0; j != n; ++j)
			if (g[i][j] == 1 && find(fa, i) != find(fa, j)) {
				fa[find(fa, i)] = find(fa, j);
				ans.push_back(i);
				ans.push_back(j);
			}
	return ans.size() == 2 * n - 2 ? ans : nosol;
}

