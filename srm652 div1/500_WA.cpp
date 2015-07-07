#include <iostream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

const int MAXN(1010);
const long long INF(1LL << 60);

class MaliciousPath {
public:
	long long minPath(int N, int K, vector <int> from, vector <int> to, vector <int> cost);
};

int q[MAXN];
long long dist[MAXN], _dist[MAXN];
bool bo[MAXN];
vector<pair<int, int> > g[MAXN], _g[MAXN];

int next(int x) {
	return (x + 1) % MAXN;
}


void spfa(int N) {
	int t = 0;
	memset(bo, false, sizeof(bo));
	for (int i = 0; i != N; ++i) {
		dist[i] = INF;
	}
	dist[N - 1] = 0;
	bo[N - 1] = true;
	q[t++] = N - 1;
	for (int h = 0; h != t; h = next(h)) {
		for (pair<int, int> ed : _g[q[h]])
			if (dist[ed.first] > dist[q[h]] + ed.second) {
				dist[ed.first] = dist[q[h]] + ed.second;
				if (!bo[ed.first]) {
					bo[ed.first] = true;
					q[t] = ed.first;
					t = next(t);
				}
			}
		bo[q[h]] = false;
	}
}

void update_dist(int N) {
	int t = 0;
	for (int i = 0; i != N - 1; ++i) {
		q[t++] = i;
		bo[i] = true;
	}
	for (int h = 0; h != t; h = next(h)) {
		long long val = INF;
		for (pair<int, int> ed : g[q[h]]) {
			val = min(val, dist[ed.first] + ed.second);
		}
		if (val > dist[q[h]]) {
			for (pair<int, int> ed : _g[q[h]]) {
				if (dist[ed.first] == dist[q[h]] + ed.second && !bo[ed.first]) {
					bo[ed.first] = true;
					q[t] = ed.first;
					t = next(t);
				}
			}
			dist[q[h]] = val;
		}
		bo[q[h]] = false;
	}
}

long long MaliciousPath :: minPath(int N, int K, vector <int> from, vector <int> to, vector <int> cost) {
	for (int i = 0; i != from.size(); ++i) {
		g[from[i]].push_back(make_pair(to[i], cost[i]));
	    _g[to[i]].push_back(make_pair(from[i], cost[i]));
	}
	spfa(N);
	if (dist[0] == INF)
		return -1;
	for (int i = 0; i != K; ++i) {
		memcpy(_dist, dist, sizeof(dist));
		for (int j = 0; j != N - 1; ++j) {
			for (pair<int, int> ed : g[j])
				dist[j] = max(dist[j], _dist[ed.first] + ed.second);
		}
		update_dist(N);
	}
	return dist[0];
}


