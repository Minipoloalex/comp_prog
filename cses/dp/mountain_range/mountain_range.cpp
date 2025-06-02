#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> h(n);
    for (auto &hi: h) cin >> hi;
    vector<vector<int>> g(n);
    stack<pair<int,int>> s;
    for (int i = 0; i < n; i++) {
        while (!s.empty() && h[i] >= s.top().first) {
            s.pop();
        }
        if (!s.empty()) {
            g[s.top().second].push_back(i);
        }
        s.emplace(h[i], i);
    }
    s = stack<pair<int,int>>();
    for (int i = n - 1; i >= 0; i--) {
        while (!s.empty() && h[i] >= s.top().first) {
            s.pop();
        }
        if (!s.empty()) {
            g[s.top().second].push_back(i);
        }
        s.emplace(h[i], i);
    }
    vector<int> dp(n, -1);
    function<int(int)> go = [&](int u) {
        int &ans = dp[u];
        if (ans != -1) {
            return ans;
        }
        int cur = 1;
        for (int v: g[u]) {
            cur = max(cur, go(v) + 1);
        }
        return ans = cur;
    };
    int ans = 0;
    for (int i = 0; i < n; i++) {
        // cout << go(i) << " \n"[i == n - 1];
        ans = max(ans, go(i));
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
