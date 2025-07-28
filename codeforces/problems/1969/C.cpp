#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int64_t> a(n);
    for (auto &ai: a) cin >> ai;
    vector<vector<int64_t>> dp(n + 1, vector<int64_t>(k + 1, INT64_MAX));
    for (int j = 0; j <= k; j++) {
        dp[0][j] = 0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= k; j++) {
            dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + a[i]);
            int64_t mn = a[i];
            for (int ki = 1; j + ki <= k && i + ki < n; ki++) {
                mn = min(mn, a[i + ki]);
                dp[i + 1 + ki][j + ki] = min(dp[i + ki + 1][j + ki], dp[i][j] + mn * (ki + 1));
            }
        }
    }
    int64_t ans = dp[n][min(n, k)];
    cout << ans << '\n';
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
