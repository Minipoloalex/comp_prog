#include <bits/stdc++.h>
using namespace std;


void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> vis(n);
    vector<tuple<int,int,int>> ans;
    function<bool(int, int)> dfs = [&](int u, int p) {   // true if did not use the parent edge
        vis[u] = 1;
        vector<int> old, cs;
        for (int v: g[u]) {
            if (v == p) continue;
            if (!vis[v]) {
                if (dfs(v, u)) cs.push_back(v);
            }
            else {
                if (u < v) {
                    old.push_back(v);
                }
            }
        }
        // a better approach to deal with children and already visited nodes given on USACO
        // https://usaco.guide/problems/cf-wizards-tour/solution
        for (int i = 0; i < int(cs.size() / 2); i++) {
            int i1 = i * 2;
            int i2 = i * 2 + 1;
            ans.emplace_back(cs[i1], u, cs[i2]);
        }
        for (int i = 0; i < int(old.size() / 2); i++) {
            int i1 = i * 2;
            int i2 = i * 2 + 1;
            ans.emplace_back(old[i1], u, old[i2]);
        }
        int rst_c = cs.size() % 2;
        int rst_old = old.size() % 2;
        if (rst_c + rst_old == 2) {
            ans.emplace_back(cs.back(), u, old.back());
            return true;
        }
        else if (rst_c == 1 && p != -1) {
            ans.emplace_back(cs.back(), u, p);
            return false;
        }
        else if (rst_old == 1 && p != -1) {
            ans.emplace_back(old.back(), u, p);
            return false;
        }
        return true;
    };
    for (int i = 0; i < n; i++) {
        if (!vis[i]) dfs(i, -1);
    }

    cout << ans.size() << '\n';
    for (auto &[x, y, z]: ans) {
        cout << x + 1 << " " << y + 1 << " " << z + 1 << '\n';
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
