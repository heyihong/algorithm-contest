#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>

using namespace std;

class WalkingToSchool {
public:
	string canWalkExactly(int N, vector <int> from, vector <int> to);
};

vector<bool> bfs(const vector<vector<int>> & g, int s) {
	queue<int> q;
	vector<bool> visited(g.size(), false);
	q.push(s);
	visited[s] = true;	
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int v : g[u]) {
			if (!visited[v]) {
				visited[v] = true;					
				q.push(v);	
			}
		}
	}
	return visited;
}

int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}

string WalkingToSchool :: canWalkExactly(int N, vector <int> from, vector <int> to) {
	vector<vector<int>> g = vector<vector<int>>(N);
	for (int i = 0;i != from.size(); ++i) {
		g[from[i]].push_back(to[i]);
	}
	vector<bool> visited_from_0 = bfs(g, 0);
	vector<bool> visited_from_1 = bfs(g, 1);
	if (!visited_from_0[1] || !visited_from_1[0]) {
		return "Chores";
	}
	int ans = 0;
	vector<bool> reach = vector<bool>(N, false); 
	reach[0] = true;
	for (int i = 1; i <= 2 * N; ++i) {
		vector<bool> next_reach = vector<bool>(N, false);	
		for (int u = 0; u != N; ++u) {
			if (reach[u]) {
				for (int v : g[u]) {
					next_reach[v] = true;	
				}
			}
		}
		reach = next_reach;
		if (reach[0]) {
			ans = gcd(ans, i);	
		}
	}
	return ans == 1 ? "Freedom" : "Chores";
}