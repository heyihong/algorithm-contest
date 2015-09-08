#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

const int g_kMod(1000000007);

typedef pair<int, int> Edge; 

typedef vector<vector<Edge> > Graph;

inline int Mul(int a, int b) {
    return (long long) a * b % g_kMod;
}

bool traverse(const Graph & gr, vector<int> & col, int x, int c) {
    col[x] = c;
    for (Edge edge : gr[x]) {
        if (col[edge.first] == -1) {
            if (!traverse(gr, col, edge.first, c ^ edge.second)) {
                return false;
            }
        } else {
            if (col[edge.first] != (c ^ edge.second)) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    // freopen("in.txt", "r", stdin);
    int n, m;
    cin >> n >> m;
    Graph gr(n + 1);
    for (int i = 0; i != m; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        c ^= 1;
        gr[u].push_back(make_pair(v, c));
        gr[v].push_back(make_pair(u, c));
    }
    vector<int> color(n + 1, -1); 
    int result = (g_kMod + 1) / 2; 
    for (int i = 1; i <= n; ++i) {
        if (color[i] == -1) {
            if (!traverse(gr, color, i, 0)) {
                result = 0;
                break;
            }
            result = Mul(result, 2);
        }
    }
    cout << result << endl;
    return 0;
}
