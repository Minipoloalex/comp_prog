#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a;
    for (int i = 0; i < n; i++) {
        int ai;
        cin >> ai;
        if (i == 0) {
            a.push_back(ai);
        }
        else {
            if (ai == a.back()) continue;
            if (a.back() + 1 >= ai) {
                continue;
            }
            a.push_back(ai);
        }
    }
    cout << a.size() << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
