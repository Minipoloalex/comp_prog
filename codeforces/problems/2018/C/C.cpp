#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    vector<int> edges(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
        edges[u]++;
        edges[v]++;
    }
    vector<int> depth(n);
    depth[0] = 0;
    vector<vector<int>> base_leafs(n);
    vector<int> par(n);
    function<void(int,int)> dfs_depth = [&](int u, int p) {
        par[u] = p;
        for (int v: g[u]) {
            if (v != p) {
                depth[v] = depth[u] + 1;
                dfs_depth(v, u);
            }
        }
        if (edges[u] == 1 && u != 0) {
            base_leafs[depth[u]].push_back(u);
        }
    };
    dfs_depth(0, -1);
    auto handle_smaller = [&]() {
        vector<int> costs(n);   // cost to remove leafs with depth <= X
        queue<pair<int,int>> q;
        auto curedges = edges;

        for (int dep = 1; dep < n; dep++) {
            for (int l: base_leafs[dep]) {
                q.emplace(dep, l);
            }
            int cur_cost = 0;
            while (!q.empty()) {
                auto [d, u] = q.front();
                q.pop();
                cur_cost++;
                if (--curedges[par[u]] == 1 && par[u] != 0) {
                    q.emplace(d - 1, par[u]);
                }
            }
            costs[dep] = cur_cost;
            if (dep > 0) {
                costs[dep] += costs[dep - 1];
            }
        }
        return costs;
    };
    auto handle_larger = [&]() {
        vector<int> costs(n);   // cost to remove leafs with depth >= X
        auto curedges = edges;
        auto curleafs = base_leafs;
        for (int dep = n - 1; dep >= 1; dep--) {
            int cur_cost = 0;
            for (int l: curleafs[dep]) {
                cur_cost++;
                if (--curedges[par[l]] == 1 && par[l] != 0) {
                    curleafs[dep - 1].push_back(par[l]);
                }
            }
            costs[dep] = cur_cost;
            if (dep + 1 < n) {
                costs[dep] += costs[dep + 1];
            }
        }
        return costs;
    };
    vector<int> prefcosts = handle_smaller();
    vector<int> sufcosts = handle_larger();

    int ans = INT_MAX;
    for (int dep = 1; dep < n; dep++) {
        int cur = 0;
        if (dep > 0) {
            cur += prefcosts[dep - 1];
        }
        if (dep + 1 < n) {
            cur += sufcosts[dep + 1];
        }
        ans = min(ans, cur);
        // cout << dep << " " << cur << '\n';
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
