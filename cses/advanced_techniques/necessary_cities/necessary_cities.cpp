#include <bits/stdc++.h>
using namespace std;

/**
 * Finds all Articulation Points (Cut Vertices) of an UNDIRECTED graph in O(N + M)
 * 
 * Usage:
 *  ArticulationPoints ap(n, adj);
 *  ap.run([&](int u) {
 *      // handle the articulation point u
 *  });
 * 
 *  // Or collect them all
 *  auto cuts = ap.all_cutpoints();
 */
struct ArticulationPoints {
    int n;
    const vector<vector<int>> &g;

    vector<int> tin, low;
    vector<bool> vis;
    vector<bool> is_cut;
    int timer = 0;

    ArticulationPoints(int _n, const vector<vector<int>> &_g)
        : n(_n), g(_g), tin(n, -1), low(n, -1), vis(n, false), is_cut(n, false) {}

    template<class F>
    void dfs(int u, int p, F &on_cut) {
        vis[u] = true;
        tin[u] = low[u] = timer++;
        int children = 0;

        for (int v : g[u]) {
            if (v == p) continue;
            if (vis[v]) {   // back-edge
                low[u] = min(low[u], tin[v]);
            } else {    // tree-edge
                dfs(v, u, on_cut);
                low[u] = min(low[u], low[v]);

                if (p != -1 && low[v] >= tin[u]) {
                    if (!is_cut[u]) { on_cut(u); }
                    is_cut[u] = true;
                }
                children++;
            }
        }

        // root is articulation if it has more than one child
        if (p == -1 && children > 1) {
            if (!is_cut[u]) { on_cut(u); }
            is_cut[u] = true;
        }
    }

    template<class F>
    void run(F on_cut) {
        timer = 0;
        for (int i = 0; i < n; ++i)
            if (!vis[i]) dfs(i, -1, on_cut);
    }

    // Returns a sorted list of all articulation points.
    vector<int> all_cutpoints() {
        vector<int> res;
        run([&](int u){ res.push_back(u); });
        // sort(res.begin(), res.end());
        return res;
    }
};

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
    ArticulationPoints ap(n, g);
    auto cuts = ap.all_cutpoints();
    cout << cuts.size() << '\n';
    for (int v: cuts) {
        cout << v + 1 << " ";
    }
    cout << '\n';
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
