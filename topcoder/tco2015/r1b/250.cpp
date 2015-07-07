#include <iostream>
#include <vector>

using namespace std;

const int MAXV(1010);

class TheNicePair {
public:
	int solve(vector <int> A);
};

int TheNicePair :: solve(vector <int> A) {
	int n = A.size();
	vector<int> B(A.size() + 1, 0);
	int maxk = -1;
	for (int v = 2; v <= MAXV; ++v) {
		for (int i = 1; i <= n; ++i)
			B[i] = B[i - 1] + (A[i - 1] % v == 0);
		for (int i = 1; i <= n; ++i)
			for (int j = i; j <= n; ++j)
				if (2 * (B[j] - B[i - 1]) >= j - i + 1) {
					//cout << i << " " << j << " " << v  << " " << B[j] - B[j - 1] << endl;
					maxk = max(maxk, j - i);
				}
	}
	return maxk;
}

