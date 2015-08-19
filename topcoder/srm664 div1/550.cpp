#include <iostream>
#include <vector>

using namespace std;

const int MAXN(1000010), MOD(1000000007);

class BearAttacks {
public:
    int expectedValue(int N, int R0, int A, int B, int M, int LOW, int HIGH);
};

inline int add(int a, int b) {
    return (a + b) % MOD;
}

inline int sub(int a, int b) {
    return (a + MOD - b) % MOD;
}

inline int mul(int a, int b) {
    return ((long long) a * b) % MOD;
}

int pow(int a, int b) {
    if (b == 0) {
        return 1;
    }
    int t = pow(a, b / 2);
    t = mul(t, t);
    return b % 2 ? mul(t, a) : t;
}

vector<int> g[MAXN];

int ans[MAXN], ex[MAXN], ex2[MAXN], inv[MAXN];

void count(int x, int fa) {
    int survive = 1;
    int no_survive = 0;
    ex[x] = ex2[x] = 1;
    for (auto y : g[x])
       if (y != fa) {
            count(y, x);
            int new_ex = add(ex[x], ex[y]);
            int new_ex2 = add(ex2[x], add(ex2[y], mul(2, mul(ex[x], ex[y])))); 
            survive = add(new_ex2, add(sub(survive, ex2[x]), sub(ans[y], ex2[y])));
            no_survive = add(no_survive, ans[y]);
            ex[x] = new_ex;
            ex2[x] = new_ex2;
       } 
    ex[x] = mul(ex[x], inv[x]);
    ex2[x] = mul(ex2[x], inv[x]);
    ans[x] = add(mul(inv[x], survive),  mul(sub(1, inv[x]), no_survive));
}

int BearAttacks :: expectedValue(int N, int R0, int A, int B, int M, int LOW, int HIGH) {
    int R = R0;
    int BILLION = 1000000000;
    for (int i = 1; i != N; ++i) {
        R = ((long long) A * R + B) % M;
        int MIN = ((long long)(i - 1) * LOW) / BILLION;
        int MAX = ((long long)(i - 1) * HIGH) / BILLION;
        pair<int, int> edge = make_pair(i, MIN + (R % (MAX - MIN + 1)));
        ++edge.first; ++edge.second;
        g[edge.first].push_back(edge.second);
        g[edge.second].push_back(edge.first);
    }
    inv[0] = 1;
    for (int i = 1; i <= N; ++i) {
        inv[i] = pow(i, MOD - 2);
    }
    count(1, 0);
    int result = ans[1];
    for (int i = 1; i <= N; ++i)
    	result = mul(result, i);
    return result;
}
