#include <iostream>
#include <string>

using namespace std;

class AB {
public:
	string createString(int N, int K);
};

string AB :: createString(int N, int K) {
	for (int b = 0; b <= N; ++b) {
		int tb = b, ta = N - b, tk = K;
		string str = "";
		for (; tb && tk >= ta; --tb, tk -= ta)
			str = "B" + str;
		if (tb == 0 && tk > 0) continue;
		for (int i = 0; i != ta - tk; ++i)
			str = "A" + str;
		if (tb > 0) 
			str = "B" + str;
		for (int i = 0; i != tk; ++i)
			str = "A" + str;
		for (int i = 0; i < tb - 1; ++i) 
			str = "B" + str;
		return str;
	}
	return "";
}