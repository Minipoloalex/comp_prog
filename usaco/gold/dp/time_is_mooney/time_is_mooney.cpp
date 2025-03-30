#include <bits/stdc++.h>
using namespace std;

const int MAX_T = int(1e3);

void solve() {
    int n, m, c;
    cin >> n >> m >> c;
    vector<int> moo(n);
    for (auto &x: moo) cin >> x;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        g[a].push_back(b);
    }
    vector<vector<int>> dp(n + 1, vector<int>(MAX_T + 1, INT_MIN));
    dp[0][0] = 0;
    int ans = 0;
    for (int t = 1; t <= MAX_T; t++) {
        for (int i = 0; i < n; i++) {
            if (dp[i][t - 1] == INT_MIN) continue;
            for (int v: g[i]) {
                dp[v][t] = max(dp[v][t], dp[i][t - 1] + moo[v]);
            }
        }
        if (dp[0][t] != INT_MIN) {
            ans = max(ans, dp[0][t] - c * t * t);
        }
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    freopen("time.in", "r", stdin);
    freopen("time.out", "w", stdout);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
