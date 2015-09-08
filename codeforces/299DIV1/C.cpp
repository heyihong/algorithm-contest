#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

struct Competitor {
    int s, r;

    bool operator<(const Competitor & other) const {
        return s < other.s || (s == other.s && r < other.r);
    }        

    bool operator==(const Competitor & other) const {
        return s == other.s && r == other.r;
    }
};

typedef pair<double, double> Range;

double Slope(const Competitor & a, const Competitor & b) {
    return (1.0 / a.r - 1.0 / b.r) / (1.0 / a.s - 1.0 / b.s);
}

int Sign(double a) {
    static const double kEps = 1e-7;
   if (fabs(a) < kEps) {
        return 0;
    } 
    return a >= kEps ? 1 : -1;
}

int main() {
    int n;
    //freopen("in.txt", "r", stdin);
    cin >> n;
    vector<Competitor> crs(n);
    map<Competitor, vector<int> > idx;
    for (int i = 0; i != n; ++i) {
        cin >> crs[i].s >> crs[i].r;
        idx[crs[i]].push_back(i + 1);
    }    
    sort(crs.begin(), crs.end());
    int size = 0;
    for (int i = 0; i != crs.size(); ++i) {
        if (i == crs.size() - 1 || crs[i].s != crs[i + 1].s) {
            crs[size++] = crs[i];
        }
    }
    crs.erase(crs.begin() + size, crs.end());
    
    vector<Competitor> stk;
    vector<Range> ranges(crs.size());
    for (int i = 0; i != crs.size(); ++i) {
        int top = stk.size();
        while (top >= 2 && Slope(stk[top - 2], stk[top - 1]) < Slope(stk[top - 1], crs[i])) {
            --top;
            stk.pop_back();
        }
        if (top == 0) {
            ranges[i].first = 0;
        } else {
            ranges[i].first = max(0.0, -Slope(stk[top - 1], crs[i]));
        }
        stk.push_back(crs[i]);
    }   
    stk.clear();
    for (int i = crs.size() - 1; i != -1; --i) {
        int top = stk.size();
        while (top >= 2 && Slope(stk[top - 2], stk[top - 1]) > Slope(stk[top - 1], crs[i])) {
            --top;
            stk.pop_back();
        }
        if (top == 0) {
            ranges[i].second = 1e10;
        } else {
            ranges[i].second = -Slope(stk[top - 1], crs[i]);
        }
        stk.push_back(crs[i]);
    }   
    vector<int> result;
    for (int i = 0; i != crs.size(); ++i) {
        if (Sign(ranges[i].second) > 0 && Sign(ranges[i].first - ranges[i].second) <= 0) {
            vector<int> temp = idx[crs[i]];
            result.insert(result.end(), temp.begin(), temp.end());
        }
    }
    sort(result.begin(), result.end());
    for (int i = 0; i != result.size(); ++i) {
        if (i == result.size() - 1) {
            cout << result[i] << endl;
        } else {
            cout << result[i] << " ";
        }
    }
    return 0;
}
