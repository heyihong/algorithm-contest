#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> ToDigits(int n) {
    vector<int> result;
    for (; n; n /= 10) {
        result.push_back(n % 10);
    }
    return result;
}

int main() {
    //freopen("in.txt", "r", stdin);
    int n;
    cin >> n;
    vector<int> digits = ToDigits(n); 
    int p = 1;
    vector<int> numbers;
    for (int digit : digits) {
        if (numbers.size() < digit) {
            numbers.resize(digit);
        }
        for (int i = 0; i != digit; ++i) {
            numbers[i] += p; 
        }
        p *= 10; 
    }
    cout << numbers.size() << endl;
    for (int i = 0; i != numbers.size(); ++i) {
        if (i) {
            cout << " ";
        }
        cout << numbers[i];
    }
    cout << endl;
    return 0;
}
