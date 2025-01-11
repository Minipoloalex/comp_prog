#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> g;
vector<int> vis;

bool bipartite(int u, int c) {
    vis[u] = c;
    c = 3 - c;
    bool ans = true;
    for (int v: g[u]) {
        if (!vis[v]) {
            ans &= bipartite(v, c);
        }
        else if (vis[v] != c) {
            ans = false;
        }
    }
    return ans;
}

void solve() {
    int n, m;
    cin >> n >> m;
    g.assign(n + 1, vector<int>());
    vis.assign(n + 1, 0);
    while (m--) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    bool ans = true;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            ans &= bipartite(i, 1);
        }
    }
    if (!ans) cout << "IMPOSSIBLE\n";
    else {
        for (int i = 1; i <= n; i++) {
            cout << vis[i] << " ";
        }
        cout << '\n';
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
