#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

class TheTips {
public:
	double solve(vector <string> clues, vector <int> probability);
};

double TheTips :: solve(vector <string> clues, vector <int> probability) {
	int n = clues.size();
	for (int i = 0; i != n; ++i)
		clues[i][i] = 'Y';
	for (int i = 0; i != n; ++i) {
		for (int j = 0; j != n; ++j)
			for (int k = 0; k != n; ++k)
				if (clues[j][i] == 'Y' && clues[i][k] == 'Y')
					clues[j][k] = 'Y';
	}
	double ans = 0;
	for (int i = 0; i != n; ++i) {
		double p = 1;
		for (int j = 0; j != n; ++j)
			if (clues[j][i] == 'Y') p = p * (100 - probability[j]) / 100.;
		ans += 1 - p;
	}
	return ans;
}

