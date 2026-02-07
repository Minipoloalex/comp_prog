#include <bits/stdc++.h>
using namespace std;

const int MAX_R = 20;

void solve() {
    int n;
    cin >> n;
    vector<int64_t> c(n);
    for (auto &ci: c) cin >> ci;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        x--;y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    vector<int64_t> sufmin(MAX_R+1, INT64_MAX);
    vector<vector<int64_t>> dp(n, vector<int64_t>(MAX_R, INT64_MAX));
    function<void(int,int)> dfs = [&](int u, int p) {
        for (int i = 1; i < MAX_R; i++) {
            dp[u][i] = i*c[u];
        }
        for (int v: g[u]) {
            if (v == p) continue;
            dfs(v, u);

            for (int i = MAX_R-1; i >= 1; i--) {
                sufmin[i] = min(sufmin[i+1], dp[v][i]);
            }
            int64_t mnbefore = INT64_MAX;
            for (int i = 1; i < MAX_R; i++) {
                int64_t mnafter = sufmin[i+1];
                dp[u][i] += min(mnbefore, mnafter);
                mnbefore = min(mnbefore, dp[v][i]);
            }
        }
    };
    dfs(0,-1);
    int64_t ans = *min_element(dp[0].begin(), dp[0].end());
    cout << ans << '\n';
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
