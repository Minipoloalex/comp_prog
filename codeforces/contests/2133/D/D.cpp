#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int64_t> h(n + 1);   // careful with size n + 1 and reverse
    for (int i = 0; i < n; i++) cin >> h[i];
    reverse(h.begin(), h.end());

    vector<vector<int64_t>> dp(n + 1, vector<int64_t>(2, INT64_MAX));
    dp[0][0] = 0;
    dp[0][1] = 0;
    for (int i = 1; i <= n; i++) {
        dp[i][1] = min({dp[i][1], dp[i - 1][1] + h[i]});
        if (i > 1) {
            dp[i][1] = min(dp[i][1], dp[i - 1][0] + h[i] - (h[i - 1] - 1) + max(int64_t(0), h[i - 1] - (n - i + 1)));
        }
        dp[i][0] = min({dp[i][0], dp[i - 1][0] + h[i] - 1, dp[i - 1][1] + h[i] - 1});
    }
    int64_t ans = min(dp[n][1], dp[n][0] + 1);
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
