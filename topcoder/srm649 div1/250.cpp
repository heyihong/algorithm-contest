#include <iostream>
#include <string>

using namespace std;

class Decipherability {
public:
	string check(string s, int K);
};

string Decipherability :: check(string s, int K) {
	if (K == s.size()) return "Certain";
	for (int i = 0; i != s.size(); ++i)
		for (int j = i + 1; j != s.size(); ++j)
			if (s[i] == s[j] && j - i <= K)
				return "Uncertain";
	return "Certain";

}