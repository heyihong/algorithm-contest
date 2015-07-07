#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int N(1010), C(30);

double prob[C][N];

class SquareScores {
public:
	double calcexpectation(vector <int> p, string s);
};

double SquareScores :: calcexpectation(vector <int> p, string s) {
	int n = s.size();
	double ans = 0;
	for (int i = 0; i < p.size(); ++i) {
		prob[i][0] = 1;
		double mulp = p[i] / 100.;
		for (int j = 1; j <= n; ++j) {
			prob[i][j] = prob[i][j - 1] * mulp;
		}
	}
	for (int i = 0; i != n; ++i) {
		char c = 0;
		int qm = 0;
		for (int j = i; j != n; ++j) {
			if (s[j] == '?') ++qm;
			else if (c == 0) c = s[j];
			else if (c != s[j]) break;
			if (c == 0) {
				for (int k = 0; k != p.size(); ++k)
					ans += prob[k][qm];
			}
			else {
				ans += prob[c - 'a'][qm];
			}
		}
	}
	return ans;
}