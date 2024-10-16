#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = int(1e9) + 7;
const int MAX_N = int(1e3) + 10;
int64_t dp[MAX_N][MAX_N];

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n;
    cin >> n;

    // memset(dp, 0, sizeof(dp));
    for (int i = 0; i < n; i++) {
        dp[0][i] = 1;
        dp[i][0] = 1;
    }
    for (int l = 1; l <= n - 2; l++) {
        for (int r = 1; r <= n - 2; r++) {
            dp[l][r] = (dp[l][r - 1] + dp[l - 1][r]) % MOD;
            // cout << l << " " << r << " " << dp[l][r] << " " << dp[l - 1][r] << " " << dp[l][r - 1] << endl;
        }
    }
    // cout << endl << endl;
    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int r = j - i - 1;
            int l = n - r - 2;
            // cout << i << " " << j << " " << l << " " << r << " " << dp[l][r] << endl;
            (ans += dp[l][r]) %= MOD;
        }
    }
    cout << ans << '\n';
    return 0;
}
