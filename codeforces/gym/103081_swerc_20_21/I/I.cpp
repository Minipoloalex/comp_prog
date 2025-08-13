#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    queue<int> q;
    vector<int> dist(n, -1);
    q.push(0);
    dist[0] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v: g[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (dist[i] == -1) {
            cout << "-1\n";
            return;
        }
        ans = max(ans, dist[i]);
    }
    ans = int(ceil(log2(ans))) + 1;
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
