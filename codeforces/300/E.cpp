#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

const int MaxN(200010);

vector<int> g[MaxN];

int num_leaves[MaxN];

void CountNumLeaves(int x) {
    if (g[x].size() == 0) {
        num_leaves[x] = 1;
        return;
    }
    for (int y : g[x]) {
        CountNumLeaves(y);
        num_leaves[x] += num_leaves[y];
    }
}

int PlayGame(int x, int current_player, int first_player) {
    if (g[x].empty()) {
        return 1;
    }
    int result = 0;
    if (first_player == 0) {
        if (current_player == 0) {
            result = 1;
            for (int y : g[x]) {
                int v = PlayGame(y, current_player ^ 1, first_player);
                result = max(result, num_leaves[x] - num_leaves[y] + v);
            }
        } else {
            result = 1;
            for (int y : g[x]) {
                int v = PlayGame(y, current_player ^ 1, first_player);
                result += v - 1;
            }
        }
    } else if (first_player == 1) {
        if (current_player == 0) {
            result = 0;
            for (int y : g[x]) {
                int v = PlayGame(y, current_player ^ 1, first_player);
                result += v;
            }
        } else {
            result = num_leaves[x];
            for (int y : g[x]) {
                int v = PlayGame(y, current_player ^ 1, first_player);
                result = min(result, v);
            }
        }
    }
    return result; 
}

int main() {
    //freopen("in.txt", "r", stdin);
    int n;
    cin >> n;
    for (int i = 1; i != n; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }
    CountNumLeaves(1); 
    cout << PlayGame(1, 0, 0) << " " << PlayGame(1, 0, 1) << endl;
    return 0;
}
