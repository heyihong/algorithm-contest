#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

typedef vector<vector<int> > Graph;

typedef vector<int> Dist;

Dist Bfs(const Graph & g, int src) {
    vector<int> dis(g.size(), -1);
    queue<int> qu;
    qu.push(src); 
    dis[src] = 0;
    while (!qu.empty()) {
        int u = qu.front();
        for (int v : g[u]) {
            if (dis[v] == -1) {
                dis[v] = dis[u] + 1;
                qu.push(v);
            }
        }
        qu.pop();
    }
    return dis;
}

int main() {
    //freopen("in.txt", "r", stdin);
    int n, m, s1, t1, l1, s2, t2, l2;
    cin >> n >> m;
    Graph graph(n);
    for (int i = 0; i != m; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    cin >> s1 >> t1 >> l1;
    cin >> s2 >> t2 >> l2;
    --s1; --t1; --s2; --t2;
    Dist ds1 = Bfs(graph, s1);
    Dist ds2 = Bfs(graph, s2);
    Dist dt1 = Bfs(graph, t1);
    Dist dt2 = Bfs(graph, t2);
    if (ds1[t1] > l1 || ds2[t2] > l2) {
        cout << -1 << endl; 
    } else {
        int min_edges = ds1[t1] + ds2[t2];
        for (int i = 0; i != n; ++i) {
            Dist dis = Bfs(graph, i);
            for (int j = 0; j != n; ++j) {
                if (ds1[i] + dis[j] + dt1[j] <= l1 && ds2[i] + dis[j] + dt2[j] <= l2) {
                    min_edges = min(min_edges, ds1[i] + ds2[i] + dis[j] + dt1[j] + dt2[j]);
                }
                if (ds1[i] + dis[j] + dt1[j] <= l1 && dt2[i] + dis[j] + ds2[j] <= l2) {
                    min_edges = min(min_edges, ds1[i] + ds2[j] + dis[j] + dt1[j] + dt2[i]);
                }
            }
        }
        cout << m - min_edges << endl;
    }
    return 0;
}
