#include <iostream>
#include <cstring>
#include <vector>
#include <string>

using namespace std;

class BichromePainting {
public:
	string isThatPossible(vector <string> board, int k);
};

const int N(22);


vector<string> board;
int n, m, k;
bool bo[N][N];

bool expand(int x1, int y1, int x2, int y2) {
	char c = 0;
	for (int x = x1; x <= x2; ++x)
		for (int y = y1; y <= y2; ++y)
			if (!bo[x][y]) {
				if (c == 0) {
					c = board[x][y];
				}
				else if (c != board[x][y]) {
					return false;
				}
			}
	if (c == 0) return false;
	for (int x = x1; x <= x2; ++x)
		for (int y = y1; y <= y2; ++y)
			if (!bo[x][y]) {
				bo[x][y] = true;
			}
	return true;
}

string BichromePainting :: isThatPossible(vector <string> _board, int _k) {
	board = _board; k = _k;
	n = board.size(); m = board[0].size();
	bool flag = true;
	while (flag) {
		flag = false;
		for (int i = 0; i != n - k + 1; ++i)
			for (int j = 0; j != m - k + 1; ++j)
				flag = flag || expand(i, j, i + k - 1, j + k - 1);
	}
	flag = true;
	for (int i = 0; i != n; ++i)
		for (int  j = 0; j != m; ++j)
			if (!bo[i][j]) {
				return "Impossible";
			}
	return "Possible";
}