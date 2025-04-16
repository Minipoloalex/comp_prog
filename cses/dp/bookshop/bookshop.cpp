#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> h(n), s(n);
    for (auto &hi: h) cin >> hi;
    for (auto &si: s) cin >> si;

    // top-down dp solution: 0.4s (probably not worst case since it TLEs)
    // vector<vector<int>> dp(n + 1, vector<int>(x + 1, -1));
    // function<int(int, int)> go = [&](int i, int cur) {
    //     if (i == n || cur == x) return 0;
    //     int &ans = dp[i][cur];
    //     if (ans != -1) return ans;

    //     int v = go(i + 1, cur);
    //     if (cur + h[i] <= x) {
    //         v = max(v, s[i] + go(i + 1, cur + h[i]));
    //     }
    //     ans = v;
    //     return v;
    // };
    // int ans = go(0, 0);

    vector<vector<int>> dp(n + 1, vector<int>(x + 1, 0));

    // bottom-up dp solution (direct translation of top-down solution): 8s runtime
    // for (int cur = x - 1; cur >= 0; cur--) {
    //     for (int i = n - 1; i >= 0; i--) {
    //         int v = dp[i + 1][cur];
    //         if (cur + h[i] <= x) {
    //             v = max(v, s[i] + dp[i + 1][cur + h[i]]);
    //         }
    //         dp[i][cur] = v;
    //     }
    // }
    // int ans = dp[0][0];

    // push-dp solution: 10s runtime
    // for (int cur = 0; cur <= x; cur++) {
    //     for (int i = 0; i < n; i++) {
    //         dp[i + 1][cur] = max(dp[i + 1][cur], dp[i][cur]);
    //         if (cur + h[i] <= x) {
    //             dp[i + 1][cur + h[i]] = max(dp[i + 1][cur + h[i]], dp[i][cur] + s[i]);
    //         }
    //     }
    // }
    // int ans = dp[n][x];

    // pull-dp solution: 4s runtime
    // Only this one did not TLE
    for (int i = 1; i <= n; i++) {
        int cur_price = h[i - 1];
        int cur_pages = s[i - 1];
        for (int cur = 1; cur <= x; cur++) {
            dp[i][cur] = dp[i - 1][cur];
            if (cur >= cur_price) {
                dp[i][cur] = max(dp[i][cur], cur_pages + dp[i - 1][cur - cur_price]);
            }
        }
    }
    int ans = dp[n][x];
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
