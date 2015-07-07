#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_set>

using namespace std;

const int MAXN(55), MAXM(55), MOD(1000000007);

class RookGraph {
public:
	int countPlacements(int N, vector <string> graph);
};

int m;
int comb[MAXN][MAXN];
int jc[MAXN];
int num[MAXM][MAXM];
int fa[MAXM * MAXM];

inline int add(int x, int y) {
	return (x + y) % MOD;
}

inline int mul(int x, int y) {
	return (long long) x * y % MOD;
}

int find(int x) {
	return fa[x] == -1 ? x : fa[x] = find(fa[x]);
}

bool merge(int x, int y) {
	x = find(x);
	y = find(y);
	if (x == y) {
		return false;
	}
	fa[x] = y;
	return true;
}

bool color(const vector<vector<int> > & g, int x, vector<int> & col, pair<int, int> & block) {
	if (col[x] == 0) ++block.first;
	else ++block.second;
	for (int y : g[x])
		if (col[y] == -1) {
			col[y] = col[x]	^ 1;
			if (!color(g, y, col, block)) {
				return false;
			}
		}
		else if (col[x] == col[y]) {
			return false;
		}
	return true;
}

bool get_blocks(const vector<vector<int> > & g, vector<pair<int, int> > & res) {
	vector<int> col(g.size(), -1);	
	for (int i = 0; i != g.size(); ++i) 
		if (col[i] == -1) {
			pair<int, int> block = make_pair(0, 0);
			col[i] = 0;
			if (!color(g, i, col, block)) {
				return false;
			}
			res.push_back(block);
		}
	return true;
}

int get_new_id(int x, vector<int> & new_id, vector<vector<int> > & graph) {
	if (x == -1) {
		int ret = graph.size();
		graph.push_back(vector<int>());
		return ret;
	}
	x = find(x);
	if (new_id[x] == -1) {
		new_id[x] = graph.size();
		graph.push_back(vector<int>());
	}
	return new_id[x];
}

int RookGraph :: countPlacements(int N, vector <string> graph) {
	for (int i = 0; i <= N; ++i) {
		comb[i][0] = 1;
		for (int j = 1; j <= i; ++j)
			comb[i][j] = add(comb[i - 1][j - 1], comb[i - 1][j]);	
	}
	jc[0] = 1;
	for (int i = 1; i <= N; ++i)
		jc[i] = mul(jc[i - 1], i);
	m = graph.size();
	memset(num, -1, sizeof(num));
	vector<pair<int, int> > edges;
	for (int i = 0; i != m; ++i)
		for (int j = i + 1; j != m; ++j)
			if (graph[i][j] == '1') {
				num[i][j] = num[j][i] = edges.size();
				edges.push_back(make_pair(i, j));
			}
	memset(fa, -1, sizeof(fa));
	for (auto pa : edges) {
		int u = pa.first, v = pa.second;
		for (int w = 0; w != m; ++w)
			if (num[u][w] != -1 && num[w][v] != -1) {
				merge(num[u][v], num[u][w]);
				merge(num[u][v], num[w][v]);
			}
	}
	for (int i = 0; i != edges.size(); ++i)
		if (find(i) == i) {
			int total_edges = 0;
			unordered_set<int> vertexs;
			for (int j = 0; j != edges.size(); ++j)
				if (find(i) == find(j)) {
					++total_edges;
					vertexs.insert(edges[j].first);
					vertexs.insert(edges[j].second);
				}
			int total_vertexs = vertexs.size();
			if (total_vertexs * (total_vertexs - 1) / 2 != total_edges) {
				return 0;
			}
		}
	vector<int> new_id(edges.size(), -1);
	vector<vector<int> > new_graph;
	for (int i = 0; i != m; ++i) {
		int u = -1, v = -1;
		for (int j = 0; j != m; ++j) 
			if (num[i][j] != -1) {
				int nid = get_new_id(num[i][j], new_id, new_graph);	
				if (u == -1 || u == nid) u = nid;
				else if (v == -1 || v == nid) v = nid;
				else return 0;	
			}
		if (u == -1) u = get_new_id(u, new_id, new_graph); 
		if (v == -1) v = get_new_id(v, new_id, new_graph); 
		new_graph[u].push_back(v);
		new_graph[v].push_back(u);
	}
	vector<pair<int, int> > blocks;
	if (!get_blocks(new_graph, blocks)) {
		return 0;
	}	
	int f[MAXN][MAXN], _f[MAXN][MAXN];
	memset(f, 0, sizeof(f));
	f[N][N] = 1;
	for (auto block : blocks) {
		memset(_f, 0, sizeof(_f));
		for (int i = 0; i <= N; ++i)
			for (int j = 0; j <= N; ++j) {
				if (i >= block.first && j >= block.second) {
					_f[i - block.first][j - block.second] = add(_f[i - block.first][j - block.second], 
									mul(f[i][j], mul(mul(comb[i][block.first], jc[block.first]), mul(comb[j][block.second], jc[block.second]))));
				}
				if (block.first == 1 && block.second == 1) {
					continue;
				}
				if (i >= block.second && j >= block.first) {
					_f[i - block.second][j - block.first] = add(_f[i - block.second][j - block.first], 
									mul(f[i][j], mul(mul(comb[i][block.second], jc[block.second]), mul(comb[j][block.first], jc[block.first]))));
				}
			}
		memcpy(f, _f, sizeof(_f));
	}
	int ans = 0;
	for (int i = 0; i <= N; ++i)
		for (int j = 0; j <= N; ++j)
			ans = add(ans, f[i][j]);  
	return ans;
}
