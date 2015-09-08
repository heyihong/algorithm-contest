#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

const int g_kMod(1000000007);

inline int Add(int a, int b) {
    return (a + b) % g_kMod;
}

inline int Mul(int a, int b) {
    return (long long)a * b % g_kMod;
}

int main() {
    // freopen("in.txt", "r", stdin);
    int k;
    cin >> k;
    vector<int> cnt(k);
    int total = 0;
    for (int i = 0; i != k; ++i) { 
        cin >> cnt[i];
        total += cnt[i];
    }
    vector<vector<int> > comb(total + 1, vector<int>(total + 1));
    for (int i = 0; i <= total; ++i) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            comb[i][j] = Add(comb[i - 1][j - 1], comb[i - 1][j]);
        }
    }
    int result = 1;
    for (int i = k - 1; i != -1; --i) {
        result = Mul(result, comb[total - 1][cnt[i] - 1]);
        total -= cnt[i];
    } 
    cout << result << endl;
    return 0;
}
