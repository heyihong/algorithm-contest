#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <cstdio>

using namespace std;

typedef pair<int, int> Position;

int m;

Position countPosition(int h, int a, int x, int y) {
    unordered_map<int, int> p;
    int start = 0, loop = 0;
    for (; !p.count(h); ) {
        p[h] = start++; 
        h = ((long long) h * x + y) % m;
    }
    loop = start - p[h];
    start = p[h];
    int pos = p.count(a) ? p[a] : -1; 
    if (pos < start) {
        return make_pair(pos, 0);
    }
    return make_pair(pos, loop);
}

int main() {
    //freopen("in.txt", "r", stdin);
    int h1, a1, x1, y1;
    int h2, a2, x2, y2;
    cin >> m;
    cin >> h1 >> a1 >> x1 >> y1;
    cin >> h2 >> a2 >> x2 >> y2;
    Position p1 = countPosition(h1, a1, x1, y1);
    Position p2 = countPosition(h2, a2, x2, y2); 
    if (p1.first == -1 || p2.first == -1) {
        cout << -1 << endl;
    }
    else {
        long long ans = -1;
        for (int i = 0; i != m; ++i) {
            long long day = (long long)p1.second * i + p1.first;
            if ((day - p2.first == 0) || (day - p2.first > 0 && (p2.second > 0) && (day - p2.first) % p2.second == 0)) {
                ans = day;
                break;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
