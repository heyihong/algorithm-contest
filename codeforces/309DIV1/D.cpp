#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>

using namespace std;

typedef vector<vector<int> > Graph;

int main() {
    // freopen("in.txt", "r", stdin);
    int n, m, k;
    cin >> n >> m >> k;
    Graph gr(n);
    vector<bool> is_fortress(n);
    for (int i = 0; i != k; ++i) {
        int x;
        cin >> x;
        --x;
        is_fortress[x] = true; 
    }
    for (int i = 0; i != m; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    vector<double> strength(n, 0);
    set<pair<double, int> > min_heap;
    for (int i = 0; i != n; ++i) {
        if (!is_fortress[i]) {
            for (int v : gr[i]) {
                if (!is_fortress[v]) {
                   ++strength[i]; 
                }
            } 
            min_heap.insert(make_pair(strength[i] / (double)gr[i].size(), i));
        }
    }
    double result = min_heap.begin()->first;
    int best_pos = 0;
    vector<int> removed_list;
    for (int i = 0; i != n - k; ++i) {
        auto pa = *(min_heap.begin());
        if (result < pa.first) {
            result = pa.first;
            best_pos = i;
        }
        min_heap.erase(pa); 
        for (int v : gr[pa.second]) {
            if (!is_fortress[v]) {
                min_heap.erase(make_pair(strength[v] / (double)gr[v].size(), v));
                --strength[v];
                min_heap.insert(make_pair(strength[v] / (double)gr[v].size(), v));
            } 
        }
        is_fortress[pa.second] = true;
        removed_list.push_back(pa.second);
    }
    for (int i = best_pos; i != removed_list.size(); ++i) {
        is_fortress[removed_list[i]] = false;
    }
    int count = 0;
    count = ::count(is_fortress.begin(), is_fortress.end(), false);
    cout << count << endl;
    for (int i = 0; i != n; ++i) {
        if (!is_fortress[i]) {
            if (count == 1) {
                cout << i + 1 << endl;
            } else {
                cout << i + 1 << " ";
            }
            --count;
        }
    }
    return 0;
}
