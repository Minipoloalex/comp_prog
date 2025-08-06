#include <bits/stdc++.h>
using namespace std;

void solve() {
    int m;
    int64_t x;
    cin >> m >> x;
    vector<pair<int,int>> ms(m);
    int64_t total = 0;
    for (auto &[c, h]: ms) {
        cin >> c >> h;
        total += h;
    }
    vector<vector<int64_t>> dp(m + 1, vector<int64_t>(total + 1, INT64_MAX));
    for (int i = 0; i < m; i++) {
        dp[i][0] = 0;
    }
    for (int i = 0; i < m; i++) {
        auto [ci, hi] = ms[i];
        for (int j = 0; j <= total; j++) {
            dp[i + 1][j] = min(dp[i + 1][j], dp[i][j]);
            if (dp[i][j] != INT64_MAX) {
                int64_t current_available = i * x - dp[i][j];
                if (current_available >= ci) {
                    dp[i + 1][j + hi] = min(dp[i + 1][j + hi], dp[i][j] + ci);
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= total; i++) {
        if (dp[m][i] != INT64_MAX) ans = i;
    }
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
