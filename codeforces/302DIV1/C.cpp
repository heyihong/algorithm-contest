#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void Update(int & v, int nv) {
    if (v == -1 || v > nv) {
        v = nv;
    } 
}

int main() {
    //freopen("in.txt", "r", stdin);
    int n, m;
    cin >> n >> m;
    vector<string> str(n);
    for (int i = 0; i != n; ++i) {
        cin >> str[i];
    }
    vector<vector<int> > a(n, vector<int>(m, 0));
    for (int i = 0; i != n; ++i) {
        for (int j = 0; j != m; ++j) {
            cin >> a[i][j];
        }
    }
    vector<int> f(1 << n, -1);
    f[(1 << n) - 1] = 0;
    for (int i = 0; i != m; ++i) {
        vector<int> chars[26];
        for (int j = 0; j != n; ++j) {
            chars[str[j][i] - 'a'].push_back(j);
        }
        for (int j = 0; j != 26; ++j) {                        
            if (!chars[j].empty()) {
                int sum = 0;
                int max_v = 0;
                int stat = 0;
                for (int p : chars[j]) {
                    sum += a[p][i];
                    max_v = max(max_v, a[p][i]);
                    stat |= 1 << p;
                }
                sum -= max_v;
                stat ^= (1 << n) - 1;
                for (int k = 0; k != (1 << n); ++k) {
                    if (f[k] != -1) {
                        Update(f[k & stat], f[k] + sum);
                    }
                } 
            }
        }
        for (int j = 0; j != n; ++j) {
            for (int k = 0; k != (1 << n); ++k) {
                if ((k & (1 << j)) > 0 && f[k] != -1) {
                    Update(f[k ^ (1 << j)], f[k] + a[j][i]);
                }
            }
        }
    }
    cout << f[0] << endl;
    return 0;
}
