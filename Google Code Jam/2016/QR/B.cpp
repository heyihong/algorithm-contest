#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	freopen("in.txt", "r", stdin);
	int test_cases;
	cin >> test_cases;
	for (int tc = 1; tc <= test_cases; ++tc) {
		string s;
		cin >> s;
		s += '+';
		int ans = 0;
		for (int i = 1; i != s.size(); ++i) {
			if (s[i] != s[i - 1]) {
				++ans;
			}
		}
		cout << "Case #" << tc << ": " << ans << endl;
	}
	return 0;
}
