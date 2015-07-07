#include <iostream>
#include <string>
#include <vector>

using namespace std;

class CountryGroupHard {
public:
	string solve(vector <int> a);
};

bool check(const vector<int> & a, int l, int r) {
	char num = 0;
	for (int i = l; i <= r; ++i)
		if (a[i] > 0) {
			if (num == 0)
				num = a[i];
			else if (num != a[i])
				return false;
		}
	return num > 0 ? num == r - l + 1 : true;
}

string CountryGroupHard :: solve(vector <int> a) {
	vector<int> f(a.size() + 1, 0);
	int n = a.size();
	f[0] = 1;
	for (int i = 0; i != n; ++i) {
		for (int j = i; j != n; ++j) 
			if (check(a, i, j)) f[j + 1] = min(2, f[j + 1] + f[i]);
	}
	return f[n] == 1 ? "Sufficient" : "Insufficient";
}

