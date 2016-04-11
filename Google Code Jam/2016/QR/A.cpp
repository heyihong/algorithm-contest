#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int NumberToBits(int num) {
	int res = 0;
	for (; num; num /= 10) {
		res |= 1 << (num % 10);
	}	
	return res;
}

int main() {
	int test_cases;
	freopen("in.txt", "r", stdin);
	cin >> test_cases;
	for (int tc = 1; tc <= test_cases; ++tc) {
		int n;
		cin >> n;
		cout << "Case #" << tc << ": ";
		if (n == 0) {
			cout << "INSOMNIA" << endl;
		} else {
			int s = NumberToBits(n);
			int num = n;
			for (; s != (1 << 10) - 1; ) {
				num += n;
				s |= NumberToBits(num);	
			}
			cout << num << endl;
		}
	}
	return 0;
}
