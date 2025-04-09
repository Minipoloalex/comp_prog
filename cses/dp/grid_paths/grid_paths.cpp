#include <bits/stdc++.h>
using namespace std;

const int MOD = int(1e9) + 7;

void solve() {
    int n;
    cin >> n;
    vector<string> grid(n);
    for (auto &s: grid) cin >> s;

    vector<vector<int64_t>> dp(n, vector<int64_t>(n, 0));
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '*') continue;

            if (j + 1 < n) {
                if (grid[i][j + 1] != '*') {
                    (dp[i][j + 1] += dp[i][j]) %= MOD;
                }
            }
            if (i + 1 < n) {
                if (grid[i + 1][j] != '*') {
                    (dp[i + 1][j] += dp[i][j]) %= MOD;
                }
            }
        }
    }
    if (grid[0][0] == '*') cout << "0\n";   // for the case n = 1 with *
    else cout << dp[n - 1][n - 1] << '\n';
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
