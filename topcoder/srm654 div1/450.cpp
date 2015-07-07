#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int N(2010);

class SuccessiveSubtraction2 {
public:
	vector <int> calc(vector <int> a, vector <int> p, vector <int> v);
};

int pre[N], suf[N];

vector <int> SuccessiveSubtraction2 :: calc(vector <int> a, vector <int> p, vector <int> v) {
	vector<int> res;
	for (int i = 1; i != a.size(); ++i)
		a[i] = -a[i];
	for (size_t i = 0; i != p.size(); ++i) {
		if (p[i] == 0) 
			a[p[i]] = v[i];
		else
			a[p[i]] = -v[i];
		int sum = 0, max_inc = 0;
		for (size_t j = 0; j != a.size(); ++j)
			sum += a[j];
		if (a.size() > 1) {
			int val = 0;
			for (size_t j = 2; j != a.size(); ++j) {
				val = max(val, 0) - a[j];
				pre[j] = max(val, pre[j - 1]);
			}
			val = 0;
			for (size_t j = a.size() - 1; j != 1; --j) {
				val = max(val, 0) - a[j];
				suf[j] = max(val, suf[j + 1]);
			}
			for (int j = 0; j != a.size() - 1; ++j)
				max_inc = max(max_inc, pre[j] + suf[j + 1]);
		}
		res.push_back(sum + 2 * max_inc);
	}
	return res;
}