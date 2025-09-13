#include <bits/stdc++.h>
using namespace std;

const int MAX_VI = int(1e3);

void solve() {
    int n, w;
    cin >> n >> w;
    vector<pair<int,int>> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    vector<vector<int64_t>> dp(n + 1, vector<int64_t>(MAX_VI * n + 1, INT64_MAX));
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 0;
    }
    for (int i = 1; i <= n; i++) {
        auto &[wi, vi] = a[i];
        for (int v = 0; v <= MAX_VI * n; v++) {
            dp[i][v] = dp[i-1][v];
            if (v >= vi && dp[i-1][v-vi] != INT64_MAX) {
                dp[i][v] = min(dp[i][v], dp[i-1][v-vi] + wi);
            }
        }
    }
    int64_t ans = 0;
    for (int i = 0; i <= MAX_VI * n; i++) {
        if (dp[n][i] <= w) {
            ans = i;
        }
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
