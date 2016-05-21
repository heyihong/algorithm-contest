#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

const int MOD(1000000007);

class BearCavalry {
public:
	int countAssignments(vector <int> warriors, vector <int> horses);
};

int BearCavalry :: countAssignments(vector <int> warriors, vector <int> horses) {
	int n = warriors.size();
	int ans = 0;
	int i = 0;
	for (int j = 0; j != n; ++j) {
		vector<int> w, h;	
		for (int k = 0; k != n; ++k) {
			if (i != k) {
				w.push_back(warriors[k]);
			}
		}
		for (int k = 0; k != n; ++k) {
			if (j != k) {
				h.push_back(horses[k]);
			}
		}
		sort(w.rbegin(), w.rend());
		sort(h.begin(), h.end());
		int r = 0;
		int cnt = 1;
		int prod = warriors[i] * horses[j];
		for (int l = 0; l != n - 1; ++l) {
			for (; r != n - 1 && w[l] * h[r] < prod; ++r);
			if (r - l <= 0) {
				cnt = 0;
				break;
			}
			cnt = (long long)cnt * (r - l) % MOD;
		}
		ans = (ans + cnt) % MOD;
	}
	return ans;
}
