#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int main() {
    // freopen("in.txt", "r", stdin);
    int n;
    cin >> n;
    vector<string> str(n);
    int num_x = 0;
    for (int i = 0; i != n; ++i) {
        cin >> str[i];
        for (char c : str[i]) {
            if (c == 'x') {
                ++num_x;
            }
        }
    }
    vector<vector<bool> > is_move(2 * n - 1, vector<bool>(2 * n - 1, false)); 
    for (int dx = - n + 1; dx <= n - 1; ++dx) {
        for (int dy = -n + 1; dy <= n - 1; ++dy) {
            bool flag = true;
            for (int x = 0; x != n; ++x) {
                for (int y = 0; y != n; ++y) {
                    if (str[x][y] != 'o') {
                        continue;
                    } 
                    int tx = x + dx;
                    int ty = y + dy;
                    if (tx >= 0 && tx <= n - 1 && ty >= 0 && ty <= n - 1) {
                        if (str[tx][ty] == '.') {
                            flag = false;
                        }
                    }
                }
            }
            is_move[dx + n - 1][dy + n - 1] = flag;
        }
    }
    vector<vector<bool> > visit(n, vector<bool>(n, false));
    for (int dx = - n + 1; dx <= n - 1; ++dx) {
        for (int dy = -n + 1; dy <= n - 1; ++dy) {
            if (!is_move[dx + n - 1][dy + n - 1]) {
                continue;
            }
            for (int x = 0; x != n; ++x) {
                for (int y = 0; y != n; ++y) {
                    if (str[x][y] != 'o') {
                        continue;
                    }  
                    int tx = x + dx;
                    int ty = y + dy;
                    if (tx >= 0 && tx <= n - 1 && ty >= 0 && ty <= n - 1 && str[tx][ty] == 'x' && !visit[tx][ty]) {
                        visit[tx][ty] = true;
                        --num_x;
                    }
                }
            }
        }
    }
    if (num_x == 0) {
        cout << "YES" << endl;
        for (int i = 0; i != 2 * n - 1; ++i) {
            for (int j = 0; j != 2 * n - 1; ++j) {
                if (i == n - 1 && j == n - 1) {
                    cout << "o";
                } else if (is_move[i][j]) {
                    cout << "x";
                } else {
                    cout << ".";
                }
            }
            cout << endl;
        }
    } else {
        cout << "NO" << endl;
    }
    return 0;
}
