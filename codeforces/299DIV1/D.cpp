#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

const int MaxN(2010);

const long long Inf(1L << 60);

int n, m; 

int ds[MaxN];

int dt[MaxN];

bool mark[MaxN];

int sum[MaxN][MaxN];

int num[MaxN][MaxN];

vector<pair<int, int> > g[MaxN];

void Dijkstra(int src, int* dis) {
    for (int i = 0; i != n; ++i) {
        dis[i] = Inf; 
        mark[i] = false;
    }
    for (int i = 1; i != n; ++i) {
        int min_d = Inf; 
        int k = -1;
        for (int j = 0; j != n; ++j) {
            if (!mark[j] && min_d > dis[j]) {
                min_d = dis[j];
                k = j;
            }
        }
        mark[k] = true;
        for (auto edge : g[k]) {
            dis[edge.first] = min(dis[edge.first], dis[k] + edge.second);
        }
    }
}

int main() {
    freopen("in.txt", "r", stdin);
    cin >> n >> m;
    cin >> s >> t;
    --s; --t;
    for (int i = 0; i != n; ++i) {
        cin >> p[i];
    }
    for (int i = 0; i != m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u; --v;
        g[u].push_back(make_pair(v, w));
        g[v].push_back(make_pair(u, w));
    }
    Dijkstra(s, ds);
    Dijkstra(t, dt);
    for (int i = 1; i <= n; ++i) {
        os[i] = ot[i] = i;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (ds[os[i]] > ds[os[j]]) {
                swap(os[i], os[j]);
            }
            if (dt[ot[i]] > dt[ot[j]]) {
                swap(ot[i], ot[j]);
            }
        }
    }
    for (int i = 0; i <= n; ++i) {
        memset(bo, false, sizeof(bo));
        int su = 0, nu = 0;
        for (int j = 1; j <= i; ++j) {
            bo[os[j]] = true;
            su += p[os[j]];
            ++nu;
        }
        sum[i][0] = su;
        num[i][0] = nu;
        for (int j = 1; j <= n; ++j) {
            if (!bo[ot[j]]) {
                bo[ot[j]] = true;
                su += p[ot[j]];
                ++nu;
            }
            sum[i][j] = su;
            num[i][j] = nu;
        }
    }
                              
    return 0;
}
