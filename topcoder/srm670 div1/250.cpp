#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <string>

using namespace std;

class Bracket107 {
public:
	int yetanother(string s);
};

bool IsCorrect(const string & str) {
	int cnt = 0;
	for (char c : str) {
		if (c == '(') {
			++cnt;
		} else {
			--cnt;
		}
		if (cnt < 0) {
			return false;
		}
	}	
	return cnt == 0;
}

int Bracket107 :: yetanother(string s) {
	unordered_set<string> us;
	for (int p = 0; p != s.size(); ++p) {
		string c(1, s[p]);
		string tmp = s;
		tmp.erase(p, 1);
		for (int i = 0; i <= tmp.size(); ++i) {
			string bra = tmp;
			bra.insert(i, c);
			if (IsCorrect(bra)) {
				us.insert(bra);
			}
		}
	}
	return us.size() - 1;
}