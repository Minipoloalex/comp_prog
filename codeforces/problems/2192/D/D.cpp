#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int64_t> stsum(n);
    vector<int> lvl(n);
    vector<vector<int64_t>> cost(n, vector<int64_t>(2, 0)); // (root node, used op)
    function<void(int,int)> dfs = [&](int u, int p) {
        for (int v: g[u]) {
            if (v == p) continue;
            dfs(v, u);
        }

        lvl[u] = 1; // start from 1 to avoid needing to add later
        stsum[u] = a[u];
        for (int v: g[u]) {
            if (v == p) continue;
            lvl[u] = max(lvl[u], lvl[v] + 1);
            stsum[u] += stsum[v];
        }

        int64_t costnoop = 0;
        for (int v: g[u]) {
            if (v == p) continue;
            costnoop += cost[v][0];
        }
        costnoop += (stsum[u] - a[u]); // from increasing one in depth
        cost[u][0] = costnoop;

        int64_t ansop = 0;
        for (int v: g[u]) { // taking any as 1 and all others as 0 (i.e., apply operation within some child's subtree)
            if (v == p) continue;
            ansop = max(ansop, costnoop - cost[v][0] + cost[v][1]);
        }

        // try applying operation here now: if only 1 child, then value added is 0 (max level = 0)
        int c = int(g[u].size());
        vector<int> sfmxlvl(c + 1);
        for (int i = c - 1; i >= 0; i--) {
            int v = g[u][i];
            sfmxlvl[i] = sfmxlvl[i+1];
            if (v == p) continue;
            sfmxlvl[i] = max(sfmxlvl[i], lvl[v]);
        }
        int pfmxlvl = 0;
        for (int i = 0; i < c; i++) {
            int v = g[u][i];
            if (v == p) continue;
            int mxlevel = max(pfmxlvl, sfmxlvl[i+1]);

            // place node v on the max level of others
            ansop = max(ansop, costnoop + stsum[v] * mxlevel);

            pfmxlvl = max(pfmxlvl, lvl[v]);
        }
        cost[u][1] = ansop;
    };
    dfs(0, -1);
    for (int i = 0; i < n; i++) {
        cout << max(cost[i][0], cost[i][1]) << " \n"[i == n-1];
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
