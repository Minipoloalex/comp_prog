#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int64_t> a(n);
    for (auto& x : a) cin >> x;

    vector<vector<int>> g(n);
    for (int i = 1; i < n; i++) {
        int p; cin >> p;
        g[p-1].push_back(i);
    }

    const int64_t inf = int64_t(1e18);
    vector<int64_t> subtree(n), dp(n, -inf);

    function<int64_t(int)> dfs = [&] (int u) {
        int64_t r = a[u];
        for (int c : g[u]) {
            r += dfs(c);
        }
        return subtree[u] = r;
    };

    function<void(int)> calc = [&] (int u) {
        dp[u] = subtree[u];
        int64_t childs = 0;
        for (int c : g[u]) {
            calc(c);
            childs += dp[c];
        }

        dp[u] = max(dp[u], childs);
    };

    dfs(0);
    calc(0);

    cout << max(dp[0], int64_t(0)) << endl;
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
