#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

const int MaxN(200010);

void UpdateRange(vector<int> & count, int l, int r, int d) {
    count[l] += d;
    if (r + 1 < count.size()) {
        count[r + 1] -= d;
    }
}
int main() {
    //freopen("in.txt", "r", stdin);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i != n; ++i) {
        cin >> a[i];
    }
    vector<int> count(n);
    for (int i = 1; i != n; ++i) {
        for (int l = 1, r = 0; l <= n - 1; l = r + 1) {
            int inv_k = (i - 1) / l;
            r = inv_k == 0 ? n - 1 : (i - 1) / inv_k;
            if (a[inv_k] > a[i]) {
                UpdateRange(count, l, r, 1); 
            }

        } 
    }
    for (int i = 1; i < count.size(); ++i) {
        count[i] += count[i - 1];
    }
    for (int i = 1; i != n; ++i) {
        if (i == n - 1) {
            cout << count[i] << endl;
        } else {
            cout << count[i] << " ";
        }
    } 
    return 0;
}
