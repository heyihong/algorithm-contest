#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int g_kMod(1000000007);

typedef vector<vector<int> > Graph;

inline int Mul(int a, int b) {
    return (long long)a * b % g_kMod;
}

inline int Inc(int a) {
    return (a + 1) % g_kMod;
}

void Travel(const Graph & g, int x, vector<int> & dp) {
    dp[x] = 1;
    for (int y : g[x]) {
        Travel(g, y, dp);
        dp[x] = Mul(dp[x], Inc(dp[y]));
    }
}

void CountAns(const Graph & g, const vector<int> & up, int x, int down, vector<int> & ans) {
    int product = Inc(down);
    vector<int> downs;
    for (int y : g[x]) {
        downs.push_back(product);
        product = Mul(product, Inc(up[y]));
    }
    product = 1;
    for (int i = g[x].size() - 1; i != -1; --i) {
        int y = g[x][i];
        downs[i] = Mul(downs[i], product); 
        product = Mul(product, Inc(up[y]));
    }
    for (int i = 0; i != g[x].size(); ++i) {
        int y = g[x][i];
        CountAns(g, up, y, downs[i], ans);
    }
    ans[x] = Mul(up[x], Inc(down));
}

int main() {
    int n;
    //freopen("in.txt", "r", stdin);
    cin >> n;
    Graph tree(n + 1);
    for (int i = 2; i <= n; ++i) {
        int p;
        cin >> p;
        tree[p].push_back(i);
    }
    vector<int> dp(n + 1); 
    Travel(tree, 1, dp);
    vector<int> ans(n + 1);
    CountAns(tree, dp, 1, 0, ans);
    for (int i = 1; i <= n; ++i) {
        if (i == n) {
            cout << ans[i] << endl;
        }
        else {
            cout << ans[i] << " ";
        }
    } 
    return 0;
}
