#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int64_t> s(n);
    for (auto &si: s) cin >> si;
    vector<array<int64_t, 2>> dp(n + 1, {0,0});
    vector<int64_t> pref(n, 0);
    for (int i = 0; i < n; i++) {
        pref[i] = s[i];
        if (i > 0) pref[i] += pref[i-1];
    }
    for (int i = n - 1; i >= 0; i--) {
        auto [sm, sz] = dp[i + 1];
        dp[i] = {s[i], 1};
        int64_t actual = sm + pref[i + sz] - pref[i] + s[i];
        if (actual > s[i]) {
            dp[i] = {actual, sz + 1};
        }
    }
    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, dp[i][0]);
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
