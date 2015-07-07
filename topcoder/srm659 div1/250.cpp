#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class ApplesAndOrangesEasy {
public:
	int maximumApples(int N, int K, vector <int> info);
};

void put(vector<int> & cnt, vector<int> & apple, int p, int K) {
	if (apple[p] == 1) {
		return;
	}
	for (int i = p; i < cnt.size() && p >= i - K + 1; ++i)
		if (cnt[i] == 0)
			return;
	apple[p] = 1;
	for (int i = p; i < cnt.size() && p >= i - K + 1; ++i)
		--cnt[i];
}

int ApplesAndOrangesEasy :: maximumApples(int N, int K, vector <int> info) {
	vector<int> cnt(N, K / 2);
	vector<int> apple(N);
	for (int p : info)
		put(cnt, apple, p - 1, K);
	int total = 0;
	for (int i = 0; i != N; ++i) {
		put(cnt, apple, i, K);
		total += apple[i];
	}
	return total; 
}

