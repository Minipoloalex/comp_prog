#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s;
    cin >> s;
    int sz = int(s.size());
    int64_t n = stoi(s);
    vector<int64_t> ans;
    for (int i = 1; i < sz; i++) {
        string cur = s.substr(sz-i) + s.substr(0,sz-i);
        int64_t val = stoi(cur);
        int64_t x = val - n;
        if (x > 0) {
            if (x % sz == i) {
                ans.push_back(x);
            }
        }
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for (int64_t x: ans) {
        cout << x << " ";
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
