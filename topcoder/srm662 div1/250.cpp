#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class FoxesOfTheRoundTable {
public:
	vector <int> minimalDifference(vector <int> h);
};

vector <int> FoxesOfTheRoundTable :: minimalDifference(vector <int> h) {
	size_t n = h.size();
	vector<int> pos(n);
	for (int i = 0; i != n; ++i)
		pos[i] = i;
	sort(pos.begin(), pos.end(), 
			[&](int x, int y) -> bool {
					return h[x] < h[y];
			});
	vector<int> result;
	for (int i = 0; i < n; i += 2) {
		result.push_back(pos[i]);
	}
	reverse(result.begin(), result.end());
	for (int i = 1; i < n; i += 2) {
		result.push_back(pos[i]);
	}
	return result;
}

