#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m, N, M;
    cin >> n >> m >> N >> M;
    vector<vector<int>> g(n, vector<int>(m));
    for (auto &v: g) {
        for (auto &val: v) cin >> val;
    }
    const int INF = int(2e9);
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(4, INF)));
    dp[0][0][0] = g[0][0];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // 0 1
            // 2 3
            int v = g[i][j];
            dp[i][j][1] = min(dp[i][j][1], dp[i][j][0] + (M - 1) * v);
            dp[i][j][2] = min(dp[i][j][2], dp[i][j][0] + (N - 1) * v);
            dp[i][j][3] = min(dp[i][j][1] + (N - 1) * v, dp[i][j][2] + (M - 1) * v);

            if (j + 1 < m) {
                int vnxt = g[i][j+1];
                dp[i][j+1][0] = min(dp[i][j+1][0], dp[i][j][1] + vnxt);
                dp[i][j+1][2] = min(dp[i][j+1][2], dp[i][j][3] + vnxt);
            }
            if (i + 1 < n) {
                int vnxt = g[i+1][j];
                dp[i+1][j][0] = min(dp[i+1][j][0], dp[i][j][2] + vnxt);
                dp[i+1][j][1] = min(dp[i+1][j][1], dp[i][j][3] + vnxt);
            }
        }
    }
    cout << dp[n-1][m-1][3] << '\n';
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
