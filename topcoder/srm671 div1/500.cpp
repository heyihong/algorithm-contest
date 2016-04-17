#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>

using namespace std;

class BearDarts {
public:
	long long count(vector <int> w);
};

int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}

long long BearDarts :: count(vector <int> w) {		
	map<pair<int, int>, int> hash_table;
	long long result = 0;
	for (int i = 0; i != w.size(); ++i) {
		for (int j = i + 1; j != w.size(); ++j) {
			int g = gcd(w[i], w[j]);
			result += hash_table[make_pair(w[i] / g, w[j] / g)];		
		}
		for (int j = 0; j != i; ++j) {
			int g = gcd(w[i], w[j]);
			hash_table[make_pair(w[i] / g, w[j] / g)] += 1;
		}	
	}
	return result;
}
