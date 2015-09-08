#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N(200010), M(500010);

int n, q;
int a[N];
int cnt[M];
vector<int> nums[M];
bool bo[N];

void update(int x, int d) {
    for (int num : nums[x])
        cnt[abs(num)] += d;
}

int count(int x) {
    int result = 0;
    for (int num : nums[x]) {
        int d = num < 0 ? -1 : 1;
        result += d * cnt[abs(num)];
    }
    return result;
}

int main() {
    //freopen("in.txt", "r", stdin);
    cin >> n >> q;
    for (int i = 0; i != n; ++i) {
        cin >> a[i];
        if (nums[a[i]].empty()) {
            int x = a[i];
            vector<int> pr;
            for (int j = 2; j * j <= x; ++j)
                if (x % j == 0) {
                    pr.push_back(j);
                    for (; x % j == 0; x /= j);
                }
            if (x > 1) {
                pr.push_back(x);
            }
            for (int j = 0; j != (1 << pr.size()); ++j) {
                int y = 1;
                for (int k = 0; k != pr.size(); ++k)
                    if (j & (1 << k)) {
                        y *= -pr[k];
                    }
                nums[a[i]].push_back(y);
            }
        }
    }
    long long ans = 0;
    for (; q; --q) {
        int x;
        cin >> x;
        --x;
        int d = bo[x] ? -1 : 1;
        if (bo[x]) {
            update(a[x], d); 
        }
        ans += d * count(a[x]); 
        if (!bo[x]) {
            update(a[x], d);
        }
        bo[x] = !bo[x];
        cout << ans << endl;
    }
    return 0;
}
