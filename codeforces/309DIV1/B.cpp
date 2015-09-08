#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

typedef long long LL;

int main() {
    //freopen("in.txt", "r", stdin);
    int n;
    LL k;
    cin >> n >> k;
    vector<int> result(n);
    vector<LL> fib(n + 1);
    fib[0] = fib[1] = 1;
    for (int i = 2; i <= n; ++i) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    for (int i = 0; i != n; ) {
        int len = 1;
        for (int j = 1; j <= n - i; ++j) {
            int remain = n - i - j;
            LL total = fib[remain];
            if (total >= k) {
                len = j;
                break;
            }
            k -= total;
        } 
        result[i] = i + len - 1;
        for (int j = 1; j != len; ++j) {
            result[i + j] = i + j - 1;
        }
        i += len;
    }
    for (int i = 0; i != n; ++i) {
        if (i == n - 1) {
            cout << result[i] + 1 << endl;
        } else {
            cout << result[i] + 1 << " ";
        }
    }
    return 0;
}
