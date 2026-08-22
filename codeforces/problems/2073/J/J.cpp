#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x, x--;
    vector<int> ia(n);
    for (int i = 0; i < n; i++) {
        ia[a[i]] = i;
    }
    auto d = [&](int x, int y) {
        return abs(ia[x] - ia[y]);
    };
    vector<vector<int64_t>> dp(n, vector<int64_t>(n, INT64_MAX));
    for (int i = 0; i < n; i++) {
        dp[i][i] = 0;
    }
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            for (int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[k][j-1]+dp[i][k]+d(k,j));
            }
        }
    }
    cout << dp[0][n-1] << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
