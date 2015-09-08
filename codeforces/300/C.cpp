#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    // freopen("in.txt", "r", stdin);
    int n, m;
    cin >> n >> m;
    vector<int> d(m, 0);
    vector<int> h(m, 0);
    for (int i = 0; i != m; ++i) {
       cin >> d[i] >> h[i]; 
    }
    int result = max(h[0] + d[0] - 1, h[m - 1] + n - d[m - 1]);
    for (int i = 1; i != m; ++i) {
        int gap = abs(h[i] - h[i - 1]);      
        int dis = d[i] - d[i - 1];
        if (gap > dis) {
            result = -1;
            break;
        }
        // gap + 2 * inc <= dis 
        int inc = (dis - gap) / 2;
        result = max(result, max(h[i], h[i - 1]) + inc);
    }
    if (result == -1) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        cout << result << endl;
    }
    return 0;
}
