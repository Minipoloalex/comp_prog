#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n, vector<int>());
    while (m--) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<int> vis(n, 0);
    auto dfs = [&](int u, auto &&self) -> void {
        vis[u] = 1;
        for (int v: g[u]) {
            if (!vis[v]) {
                self(v, self);
            }
        }
    };
    vector<int> edges;
    for (int i = 0; i < n; i++) {
        if (vis[i]) continue;

        dfs(i, dfs);
        if (i != 0) {
            edges.push_back(i);
        }
    }
    cout << edges.size() << '\n';
    for (int e: edges) cout << 1 << " " << e + 1 << " ";
    cout << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
