#include <bits/stdc++.h>
using namespace std;

const int MOD = int(1e9) + 7;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> x(n);
    for (auto &xi: x) cin >> xi;

    // top-down
    // vector<vector<int64_t>> dp(n, vector<int64_t>(m + 1, -1));
    // function<int64_t(int, int)> go = [&](int i, int prev) -> int64_t {
    //     // cout << i << " " << prev << endl;
    //     if (i == n) return 1;

    //     int64_t &ans = dp[i][prev];
    //     if (ans != -1) return ans;

    //     int cur = x[i];
    //     if (cur == 0 && prev == 0) {
    //         int64_t here = 0;
    //         for (int j = 1; j <= m; j++) {
    //             (here += go(i + 1, j))  %= MOD;
    //         }
    //         ans = here;
    //     }
    //     else if (cur == 0) {
    //         int64_t here = 0;
    //         for (int j = -1; j <= 1; j++) {
    //             if (prev + j > 0 && prev + j <= m) {
    //                 (here += go(i + 1, prev + j)) %= MOD;
    //             }
    //         }
    //         ans = here;
    //     }
    //     else if (prev != 0 && abs(cur - prev) > 1) {
    //         ans = 0;
    //     }
    //     else {
    //         ans = go(i + 1, cur);
    //     }
    //     return ans;
    // };

    // bottom-up
    vector<vector<int64_t>> dp(n, vector<int64_t>(m + 1, 0));
    if (x[0] == 0) {
        fill(dp[0].begin() + 1, dp[0].end(), 1);
    }
    else {
        dp[0][x[0]] = 1;
    }
    for (int i = 1; i < n; i++) {
        if (x[i] == 0) {
            for (int j = 1; j <= m; j++) {
                for (int k = -1; k <= 1; k++) {
                    if (j + k > 0 && j + k <= m) {
                        (dp[i][j] += dp[i - 1][j + k]) %= MOD;
                    }
                }
            }
        }
        else {
            for (int j = -1; j <= 1; j++) {
                if (x[i] + j > 0 && x[i] + j <= m) {
                    (dp[i][x[i]] += dp[i - 1][x[i] + j]) %= MOD;
                }
            }
        }
    }

    int64_t ans = (accumulate(dp[n - 1].begin() + 1, dp[n - 1].end(), 0LL)) % MOD;
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
