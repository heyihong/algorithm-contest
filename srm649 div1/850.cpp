#include <iostream>
#include <vector>

using namespace std;

class CartInSupermarket {
public:
	int calcmin(vector <int> a, int b);
};

bool check(int numCarts, int numSplits, int limitTime) {
	int time = 0;
	int numParts = 1;
	while (numParts <= numSplits) {
		numSplits -= numParts;
		numParts *= 2;
		++time;
	}
	numCarts = max(0, numCarts - (numParts - numSplits));
	return time + 1 + (numCarts + numParts + numSplits - 1) / (numParts + numSplits) <= limitTime;
}

int calc(int numCarts, int limitTime) {
	int ll = 0, rr = numCarts;
	while (ll != rr) {
		int mid = (ll + rr) / 2;
		if (check(numCarts, mid, limitTime)) rr = mid;
		else ll = mid + 1;
	}
	return ll == numCarts ? -1 : ll;
}

int CartInSupermarket :: calcmin(vector <int> a, int b) {
	int l = 1, r = 1000000000;
	while (l != r) {
		int mid = (l + r) / 2;
		int total = 0;
		bool flag = true;
		for (int cart : a) {
			int split = calc(cart, mid);
			if (split == -1) {
				flag = false;
				break;
			}
			total += split;
		}
		if (flag && total <= b) r = mid;
		else l = mid + 1;
	}
	return l;
}