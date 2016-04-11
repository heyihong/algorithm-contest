#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>

using namespace std;

class SubdividedSlimes {
public:
	int needCut(int S, int M);
};

int SubdividedSlimes :: needCut(int S, int M) {
	for (int ans = 1; ans < S; ++ans) {
		priority_queue<int> q;
		int slime = S;
		for (int i = ans + 1; i; --i) {
			q.push(- (slime / i));
			slime -= slime / i;	
		}
		int m = 0;		
		while (q.size() > 1) {
			int x = q.top();
			q.pop();
			int y = q.top();
			q.pop();
			m += x * y;
			q.push(x + y);
		}
		if (m >= M) {
			return ans;
		}
	}
	return -1;
}
 
