#include <bits/stdc++.h>
using namespace std;

const int INF = int(1e9);

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> c(n);
    for (auto &ci: c) cin >> ci;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    queue<pair<int,int>> q;
    vector<vector<array<int,2>>> dist(n, vector<array<int,2>>(n, {INF, INF}));
    for (int src = 0; src < n; src++) {
        q.emplace(src, 0);
        dist[src][src][0] = 0;
        while (!q.empty()) {
            // represents even/odd number of color changes
            auto [u, odd] = q.front(); q.pop();
            for (int v : g[u]) {
                int curodd = c[v] == c[u] ? odd : odd ^ 1;
                if (dist[src][v][curodd] == INF) {
                    dist[src][v][curodd] = dist[src][u][odd] + 1;
                    q.emplace(v, curodd);
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int x = 0; x <= k; x++) {
                int mn = min(dist[i][j][0] + x, dist[i][j][1] + k - x);
                ans = max(ans, mn);
            }
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
