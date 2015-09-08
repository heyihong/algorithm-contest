#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

const int g_kMod(1000000007);

inline int Mul(int a, int b) {
    return (long long) a * b % g_kMod;
}

inline int Add(int a, int b) {
    return (a + b) % g_kMod;
}

inline int Sub(int a, int b) {
    return (a + g_kMod - b) % g_kMod;
}

class RollingHash {
public:
    RollingHash(const string & s) {
        hash_value = 0;
        hash_pow = 1;
        for (char ch : s) {
            hash_value = Add(Mul(hash_value, kHashP), ch - 'a'); 
            hash_pow = Mul(hash_pow, kHashP);
            chars.push(ch);
        }
    }

    void Roll(char ch) {
        chars.push(ch);
        hash_value = Add(Mul(hash_value, kHashP), ch - 'a'); 
        char old_ch = chars.front();
        hash_value = Sub(hash_value, Mul(hash_pow, old_ch - 'a'));
        chars.pop();
    }
    
    int get_hash_value() const {
        return hash_value;
    }
private:
    const int kHashP = 29;

    int hash_pow;
    int hash_value;
    queue<char> chars;
};


int main() {
    int n, m;
    string p;
    // freopen("in.txt", "r", stdin);
    cin >> n >> m;
    cin >> p;
    vector<int> y(m + 1);
    for (int i = 0; i != m; ++i) {
        cin >> y[i];
        --y[i];
    }
    y[m] = n;
    string str(n, 'a');
    int len_remain = y[0];
    for (int i = 0; i != m; ++i) {
        for (int j = y[i]; j != y[i + 1] && j - y[i] != p.size(); ++j) {
            str[j] = p[j - y[i]];
        }
        len_remain += max(0, (int)(y[i + 1] - y[i] - p.size()));
    }
    int ans = 1;
    for (; len_remain; --len_remain) {
        ans = Mul(ans, 26);
    }
    RollingHash hash_p(p);
    RollingHash hash_s(str.substr(0, p.size()));
    int idx = 0;
    for (int i = 0; i <= n - p.size() && idx != m; ++i) {
        if (i == y[idx]) {
            if (hash_p.get_hash_value() != hash_s.get_hash_value()) {
                ans = 0;
                break; 
            }
            ++idx;
        } 
        if (i != n - p.size()) {
            hash_s.Roll(str[i + p.size()]);
        }
    }
    cout << ans << endl;
    return 0;
}
