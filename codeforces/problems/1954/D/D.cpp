#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = 998244353;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    int sm = accumulate(a.begin(), a.end(), 0);
    vector<vector<int64_t>> dp(n + 1, vector<int64_t>(sm + 1, 0));
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int si = 0; si <= sm; si++) {
            dp[i][si] = (dp[i][si] + dp[i - 1][si]) % MOD;
            if (si - a[i] >= 0) {
                dp[i][si] = (dp[i][si] + dp[i - 1][si - a[i]]) % MOD;
            }
        }
    }
    int64_t ans = 0;
    for (int si = 0; si <= sm; si++) {
        int64_t val = (si + 1) / 2; // ceil(si, 2)
        int64_t cnt = dp[n][si];
        ans = (ans + cnt * val) % MOD;
    }
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w < a[i]; w++) {
            int64_t cnt = dp[n][w];
            int64_t val = (a[i] + w + 1) / 2;
            ans = (ans + (a[i] - val) * cnt) % MOD;
        }
    }
    cout << (ans + MOD) % MOD << '\n';
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
