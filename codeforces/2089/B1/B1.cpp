#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(n);
    for (auto &ai: a) cin >> ai;
    for (auto &bi: b) cin >> bi;
    stack<pair<int,int>> s;
    vector<int> ans(n);
    for (int i = 0; i < 2*n; i++) {
        if (i < n && a[i] > 0) {
            s.emplace(i, a[i]);
        }
        int j = i % n;
        while (!s.empty() && b[j] > 0) {
            auto [idx, v] = s.top(); s.pop();
            int mn = min(v, b[j]);
            v -= mn;
            b[j] -= mn;
            if (v > 0) s.emplace(idx, v);   // means b[i] == 0
            else {
                ans[idx] = i - idx + 1;
            }
        }
    }
    assert(s.empty());
    cout << *max_element(ans.begin(), ans.end()) << '\n';
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
