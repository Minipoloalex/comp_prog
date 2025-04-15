#include <bits/stdc++.h>
using namespace std;

const int MOD = int(1e9) + 7;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        g[a - 1].push_back(b - 1);
    }
    vector<vector<int>> dp(1 << n, vector<int>(n, 0));
    dp[1][0] = 1;
    for (int mask = 1; mask < (1 << n); mask++) {
        if (!(mask & 1)) continue;  // only need to consider those that have the 1st city visited
        if (mask & (1 << (n - 1))) continue;    // no need to push dp stuff anywhere if we have the last city

        // from the 2^N possible masks, only (2^N) / 4 have the first city visited and the last not visited
        // instead of 4e8, we have 1e8, which passes
        for (int u = 0; u < n; u++) {
            for (int v: g[u]) {
                if (!(mask & (1 << v))) {  // not visited
                    (dp[mask | (1 << v)][v] += dp[mask][u]) %= MOD;
                }
            }
        }
    }
    int ans = dp[(1 << n) - 1][n - 1];
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
