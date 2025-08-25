#include <bits/stdc++.h>
using namespace std;

typedef vector<int64_t> vi;
typedef vector<vi> vvi;

void solve() {
    int n, m;
    int64_t k;
    cin >> n >> m >> k;
    vvi g(n, vi(m));
    for (auto &row: g) {
        for (auto &val: row) cin >> val;
    }

    vvi dp(n, vi(m, INT64_MAX));
    for (int i = 0; i < n; i++) {
        vi &row = g[i];

        vi &dpCUR = dp[i];
        vi dpPREV;
        if (i > 0) dpPREV = dp[i - 1];
        else {
            dpPREV = vi(m, INT64_MAX);
            dpPREV[0] = 0;
        }
        
        for (int x = 0; x < m; x++) {
            vi shifted_row(m);
            for (int u = 0; u < m; u++) {
                shifted_row[u] = row[(x + u) % m];
            }
            vi cycleDP(m, INT64_MAX);
            int64_t cycleCOST = x * k;
            for (int j = 0; j < m; j++) {
                if (j > 0) {
                    cycleDP[j] = cycleDP[j - 1] + shifted_row[j];
                }
                if (dpPREV[j] != INT64_MAX) {
                    cycleDP[j] = min(cycleDP[j], dpPREV[j] + shifted_row[j]);
                }

                dpCUR[j] = min(dpCUR[j], cycleDP[j] + cycleCOST);
            }
        }
    }
    cout << dp[n - 1][m - 1] << '\n';
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
