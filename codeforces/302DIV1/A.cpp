#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

inline int Add(int x, int y, int mod) {
    return (x + y) % mod;
}

int main() {
    int n, m, b, mod;
    //freopen("in.txt", "r", stdin);
    cin >> n >> m >> b >> mod;
    vector<int> a(n);
    for (int i = 0; i != n; ++i) {
        cin >> a[i];
    }
    vector<vector<int> > dp(m + 1, vector<int>(b + 1, 0));
    dp[0][0] = 1;
    for (int i = 0; i != n; ++i) {
        for (int j = 1; j <= m; ++j) {
            for (int k = b; k >= a[i]; --k) {
                dp[j][k] = Add(dp[j][k], dp[j - 1][k - a[i]], mod);
            }
        }
    }
    int result = 0;
    for (int i = 0; i <= b; ++i) {
        result = Add(result, dp[m][i], mod);
    }
    cout << result << endl;
    return 0;
}
