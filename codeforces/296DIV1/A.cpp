#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

inline void Cut(set<int> & lines, multiset<int> & gaps, int x) {
    lines.insert(x);
    auto iter = lines.find(x);
    int left = *(--iter);
    int right = *(++(++iter)); 
    gaps.erase(gaps.find(right - left));
    gaps.insert(x - left);
    gaps.insert(right - x);
    lines.insert(x);
}

inline int MaxGap(const multiset<int> & gaps) {
    return *(--gaps.end());
}

int main() {
    int w, h, n;
    //freopen("in.txt", "r", stdin);
    cin >> w >> h >> n;
    set<int> ver, hor;
    multiset<int> ver_gap, hor_gap;
    ver.insert(0);
    ver.insert(w);
    ver_gap.insert(w);
    hor.insert(0);
    hor.insert(h);
    hor_gap.insert(h);
    for (int i = 0; i != n; ++i) {
        string dir;
        int dis;
        cin >> dir >> dis;
        if (dir == "V") {
            Cut(ver, ver_gap, dis);
        } else {
            Cut(hor, hor_gap, dis);
        }
        cout << (long long)MaxGap(ver_gap) * MaxGap(hor_gap) << endl;
    }
    return 0;
}

