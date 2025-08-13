#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m, L, U; cin >> n >> m >> L >> U;

    using edge = array<int, 2>;
    vector<set<edge>> g(n);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].insert({v, w});
        g[v].insert({u, w});
    }

    int cnt = 0;
    const int inf = int(1e8);
    
    vector<int> d(n, inf);
    vector<bool> vis(n);
    
    set<array<int, 2>> q;
    q.insert({ 0, 0 }); 
    d[0] = 0;

    while (!q.empty()) {
        auto [dist, node] = *q.begin();
        q.erase(q.begin());

        if (dist * 2 >= U) continue;

        vis[node] = 1;
        for (auto [to, w] : g[node]) {
            if (!vis[to]) cnt++;
            if (d[node] + w < d[to]) {
                q.erase({ d[to], to });
                d[to] = d[node] + w;
                q.insert({ d[to], to });
            }
        }
    }

    cout << cnt << endl;
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
