#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

string solve(int n, int r, int p, int s) {
	if (n == 0) {
		if (r) {
			return "R";	
		} if (p) {
			return "P";	
		} else {
			return "S";
		}
	}
	int sum = (r + p + s) / 2;	
	if (sum < r || sum < p || sum < s) {
		return "IMPOSSIBLE";	
	}
	string tmp = solve(n - 1, sum - p, sum - s, sum - r);
	if (tmp == "IMPOSSIBLE") {
		return tmp;
	}
	string res = "";
	for (int i = 0; i != tmp.size(); ++i) {
		if (tmp[i] == 'R') {
			res += "RS";
		} else if (tmp[i] == 'P') {
			res += "PR";	
		} else {
			res += "SP";	
		}
	}
	return res;
}
 string alphasort(int n, string str) {
 	for (int i = 1; i <= n; ++i) {
 		string tmp = "";
 		for (int j = 0; j != (1 << n); j += 1 << i) {
 			string left = str.substr(j, 1 << (i - 1));
 			string right = str.substr(j + (1 << (i - 1)), 1 << (i - 1));
 			if (left < right) {
 				tmp += left + right;	
 			} else {
 				tmp += right + left;	
 			}
 		}
	 	str = tmp;
 	}	
 	return str;
 }

int main() {
	int test_cases;
	cin >> test_cases;
	int n, r, p, s;
	for (int tc = 1; tc <= test_cases; ++tc) {
		cin >> n >> r >> p >> s;	
		string res = solve(n, r, p, s);		
		if (res == "IMPOSSIBLE") {
			cout << "Case #" << tc << ": " << res << endl;
		} else {
			cout << "Case #" << tc << ": " << alphasort(n, res) << endl;	
		}
	}		
	return 0;
}