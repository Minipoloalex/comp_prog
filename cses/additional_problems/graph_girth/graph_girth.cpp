#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    int ans = INT_MAX;
    auto bfs = [&](int s) {
        vector<int> dist(n, -1), p(n, -1);
        queue<int> q;
        q.push(s);
        dist[s] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v: g[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    p[v] = u;
                    q.push(v);
                }
                else if (p[u] != v) {
                    ans = min(ans, dist[v] + dist[u] + 1);
                }
            }
        }
    };
    for (int i = 0; i < n; i++) {
        bfs(i);
    }
    if (ans == INT_MAX) ans = -1;
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
