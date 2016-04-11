#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

class OrderOfOperations {
public:
	int minTime(vector <string> s);
};

void update(int &v, int nv) {
	if (v == -1 || v > nv) {
		v = nv;
	}	
}

int countOne(int s) {
	return s == 0 ? 0 : (countOne(s & (s - 1)) + 1);	
}

int sqr(int x) {
	return x * x;
}

int OrderOfOperations::minTime(vector <string> s) {
	int n = s.size();
	int m = s[0].size();
	vector<int> bits;
	for (string str : s) {
		int st = 0;
		for (int idx = 0; idx != m; ++idx) {
			if (str[idx] == '1') {
				st |= 1 << idx;	
			}
		}	
		bits.push_back(st);
	}
	vector<int> dp = vector<int>(1 << m, -1);	
	dp[0] = 0;
	int result = 0;
	for (int st = 0; st != (1 << m); ++st) {
		if (dp[st] != -1) {
			for (int i = 0; i != n; ++i) {
				update(dp[st | bits[i]], dp[st] + sqr(countOne(bits[i] ^ (bits[i] & st))));	
			}
			result = dp[st];
		}
	}
	return result;
}