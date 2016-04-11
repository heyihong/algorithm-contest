#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

class PaintTheRoom {
public:
	string canPaintEvenly(int R, int C, int K);
};

string PaintTheRoom :: canPaintEvenly(int R, int C, int K) {
	return ((K == 1) || (R % 2 == 0) || (C % 2 == 0)) ? "Paint" : "Cannot paint";
}