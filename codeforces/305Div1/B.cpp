#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int N(200010);

int n;
int a[N];
int ord[N];
int fa[N];
int cnt[N];
int ans[N];

bool cmp(int x, int y) {
    return a[x] > a[y];
}

int find(int x) {
    return fa[x] == -1 ? x : fa[x] = find(fa[x]);
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    cnt[x] += cnt[y];
    fa[y] = x;
}

int main() {
    //freopen("in.txt", "r", stdin);
    cin >> n;
    for (int i = 0; i != n; ++i) {
        cin >> a[i];
        ord[i] = i; 
    }
    sort(ord, ord + n, cmp);
    memset(fa, -1, sizeof(fa));
    for (int i = 0; i != n; ++i) {
        int p = ord[i];
        cnt[p] = 1;
        if (p && cnt[find(p - 1)] > 0) {
            merge(p - 1, p);
        }
        if (p != n - 1 && cnt[find(p + 1)] > 0) {
            merge(p, p + 1);
        }
        if (ans[cnt[find(p)]] == 0) {
            ans[cnt[find(p)]] = a[p];
        }
    }
    for (int i = n - 1; i ; --i)
        ans[i] = max(ans[i + 1], ans[i]);
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
