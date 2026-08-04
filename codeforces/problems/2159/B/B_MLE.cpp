#include <bits/stdc++.h>
using namespace std;

// MLEs because of space complexity O(min(n,m)*n*m)

void solve() {
    int n, m;
    cin >> n >> m;
    bool t = n > m;
    vector<vector<char>> g;
    if (t) {
        g.assign(m, vector<char>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> g[j][i];
            }
        }
        swap(n, m);
    }
    else {
        g.assign(n, vector<char>(m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> g[i][j];
            }
        }
    }

    vector<vector<array<int,3>>> colrects(m);
    for (int u = 0; u < n; u++) {
        for (int d = u+1; d < n; d++) {
            vector<int> cols;
            for (int j = 0; j < m; j++) {
                if (g[u][j] == '1' && g[d][j] == '1') {
                    cols.push_back(j);
                }
            }
            for (int i = 1; i < int(cols.size()); i++) {
                int area = (d-u+1)*(cols[i]-cols[i-1]+1);
                for (int j = cols[i-1]; j <= cols[i]; j++) {
                    colrects[j].push_back({u, d, area});
                }
            }
        }
    }

    // for each column, need to get what rectangles cover it
    vector<vector<int>> dp;

    vector<vector<int>> ans;
    if (t) ans.assign(m, vector<int>(n));
    else ans.assign(n, vector<int>(m));

    for (int j = 0; j < m; j++) {
        dp.assign(n, vector<int>(n, INT_MAX));
        for (auto &[u, d, area]: colrects[j]) {
            dp[u][d] = min(dp[u][d], area);
        }
        // process from largest interval to smallest interval to make sure that all larger intervals have been processed
        // when going over (u, d)
        for (int len = n; len >= 2; len--) {
            for (int u = 0; u + len - 1 < n; u++) {
                int d = u + len - 1;
                dp[u+1][d] = min(dp[u+1][d], dp[u][d]);
                dp[u][d-1] = min(dp[u][d-1], dp[u][d]);
            }
        }
        for (int i = 0; i < n; i++) {
            int v = dp[i][i] == INT_MAX ? 0 : dp[i][i];
            if (t) ans[j][i] = v;
            else ans[i][j] = v;
        }
    }
    for (auto &v: ans) {
        for (auto &x: v) {
            cout << x << " ";
        }
        cout << '\n';
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
