#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN(55);

class ABBADiv1 {
public:
	string canObtain(string initial, string target);
};

string initial;
string target;
int f[MAXN][MAXN][2];

int dp(int l, int r, int rev) {
	if (f[l][r][rev] != -1) {
		return f[l][r][rev];
	}
	if (r - l + 1 <= initial.size()) {
		string str = target.substr(l, r - l + 1);
		if (rev) {
			reverse(str.begin(), str.end());
		}
		return f[l][r][rev] = (initial == str);
	}
	f[l][r][rev] = 0;
	if (!rev) {
		if (target[r] == 'A') {
			f[l][r][rev] |= dp(l, r - 1, 0);
		}
		if (target[l] == 'B') {
			f[l][r][rev] |= dp(l + 1, r, 1);
		}
	}
	else {
		if (target[l] == 'A') {
			f[l][r][rev] |= dp(l + 1, r, 1);
		}
		if (target[r] == 'B') {
			f[l][r][rev] |= dp(l, r - 1, 0);
		}
	}
	return f[l][r][rev];
}

string ABBADiv1 :: canObtain(string _initial, string _target) {
	initial = _initial;
	target = _target;
	memset(f, -1, sizeof(f));	
	return dp(0, target.size() - 1, 0) ? "Possible" : "Impossible"; 
}

