#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<string> grid(n, string(n, '0'));
    vector<int> vis(n, 0);
    function<void(int,int,int)> dfs = [&](int src, int u, int c) {
        vis[u] = 1;
        for (int v: g[u]) {
            if (!vis[v] && (a[v] & (1 << c))) {
                grid[src][v] = '1';
                dfs(src, v, c);
            }
        }
    };
    for (int i = 0; i < n; i++) {
        grid[i][i] = '1';
        for (int c = 0; c < 31; c++) {
            if (a[i] & (1 << c)) {
                vis.assign(n, 0);
                dfs(i, i, c);
            }
        }
    }
    for (string s: grid) {
        cout << s << '\n';
    }
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
