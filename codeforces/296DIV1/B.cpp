#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int n;
    //freopen("in.txt", "r", stdin);
    cin >> n;
    vector<pair<int, int> > pairs;
    for (int i = 0;i != n; ++i) {
        int x, w;
        cin >> x >> w;
        pairs.push_back(make_pair(x + w, x - w));
    }
    sort(pairs.begin(), pairs.end());
    vector<int> f(n + 1); 
    for (int i = 1; i <= n; ++i) {
        auto pair = make_pair(pairs[i - 1].second, pairs[i - 1].first);
        int pos = upper_bound(pairs.begin(), pairs.end(), pair) - pairs.begin();
        f[i] = max(f[i - 1], f[pos] + 1);
    }
    cout << f[n] << endl;
    return 0;
}
