#include <iostream>

using namespace std;

typedef long long LL;

LL sum(LL a, LL b, LL l, LL r) {
    LL first = a + b * (l - 1);
    LL last = a + b * (r - 1);
    return (first + last) * (r - l + 1) / 2;
}

int main() {
    //freopen("in.txt", "r", stdin);
    LL a, b;
    int n;
    cin >> a >> b >> n;
    for (; n; --n) {
        LL left, t, m;
        cin >> left >> t >> m;
        LL l = left - 1, r = (t - a) / b + 1;
        while (l < r) {
            LL right = (l + r + 1) / 2;
            if (sum(a, b, left, right) <= t * m) {
                l = right;
            } else {
                r = right - 1;
            }
        }
        cout << (l == left - 1 ? -1 : l) << endl;
    }
    return 0;
}

