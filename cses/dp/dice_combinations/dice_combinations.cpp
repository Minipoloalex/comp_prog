#include <bits/stdc++.h>
using namespace std;

const int MOD = int(1e9) + 7;

void solve() {
    int n;
    cin >> n;
    vector<int64_t> dp(n + 1);
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= 6; j++) {
            if (i + j <= n) {
                (dp[i + j] += dp[i]) %= MOD;
            }
        }
    }
    cout << dp[n] << '\n';
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
