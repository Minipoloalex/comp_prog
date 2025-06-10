#include <bits/stdc++.h>
using namespace std;

bool bad(vector<vector<int>> &g, int n) {
    vector<int> vis(n);
    bool possible = true;
    function<void(int)> dfs = [&](int u) {
        vis[u] = 1;
        for (int v: g[u]) {
            if (!vis[v]) {
                dfs(v);
            }
            else if (vis[v] == 1) {
                possible = false;   
            }
        }
        vis[u] = 2;
    };
    for (int i = 0; i < n && possible; i++) {
        if (!vis[i]) dfs(i);
    }
    return !possible;
}

void solve() {
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    vector<vector<int>> g(n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        g[a-1].push_back(b-1);
    }
    if (bad(g, n)) {
        cout << "-1\n";
        return;
    }
    vector<vector<int>> dp(n, vector<int>(26, 0));
    vector<int> save(n);
    function<void(int)> go = [&](int u) {
        if (save[u]) return;
        save[u] = 1;

        dp[u][s[u]-'a'] = 1;
        for (int v: g[u]) {
            go(v);
            for (int j = 0; j < 26; j++) {
                dp[u][j] = max(dp[u][j], dp[v][j] + (s[u] - 'a' == j));
            }
        }
    };
    int ans = 0;
    for (int i = 0; i < n; i++) {
        go(i);
        for (int j = 0; j < 26; j++) {
            ans = max(ans, dp[i][j]);
        }
    }
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
