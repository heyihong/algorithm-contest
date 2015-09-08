#include <iostream>
#include <string>

using namespace std;

const string g_kBanner = "CODEFORCES";

int main() {
    //freopen("in.txt", "r", stdin);
    string str;
    cin >> str;
    int left = 0, right = 0;
    for (; left < g_kBanner.size() && left < str.size() && g_kBanner[left] == str[left]; ++left);
    for (; right < g_kBanner.size() && right < str.size() && g_kBanner[g_kBanner.size() - 1 - right] == str[str.size() - 1 - right]; ++right);
    cout << (left + right >= g_kBanner.size() ? "YES" : "NO") << endl;
    return 0;
}
