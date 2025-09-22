#include <bits/stdc++.h>
using namespace std;

// Tested on:
// - https://www.spoj.com/problems/EC_P/
// - CSES/Necessary-Roads

/**
 * Finds all Bridges of an UNDIRECTED graph in O(N + M)
 * 
 * Usage:
 *  Bridges b(n, adj);
 *  b.run([&](int u, int v) {
 *      // handle the bridge (u, v)
 *  });
 * 
 *  // Or collect them all
 *  auto bridges = b.all_bridges();
 */
struct Bridges {
    int n;
    const vector<vector<int>> &g;

    vector<int> tin, low;
    vector<bool> vis;
    int timer = 0;

    Bridges(int _n, const vector<vector<int>> &_g)
        : n(_n), g(_g), tin(n, -1), low(n, -1), vis(n, false) {}

    template<class F>
    void dfs(int from, int p, F &on_bridge) {
        vis[from] = true;
        tin[from] = low[from] = timer++;

        bool parent_skipped = false; // handle possible parallel edges to parent
        for (int to : g[from]) {
            if (to == p && !parent_skipped) {
                parent_skipped = true;
                continue;
            }
            if (vis[to]) {
                low[from] = min(low[from], tin[to]);
            } else {
                dfs(to, from, on_bridge);
                low[from] = min(low[from], low[to]);
                if (low[to] > tin[from]) {
                    // (from, to) is a bridge
                    on_bridge(from, to);
                }
            }
        }
    }

    template<class F>
    void run(F on_bridge) {
        timer = 0;

        for (int i = 0; i < n; i++)
            if (!vis[i]) dfs(i, -1, on_bridge);
    }

    // Returns all bridges as undirected pairs (min, max), sorted.
    vector<pair<int,int>> all_bridges() {
        vector<pair<int,int>> res;
        run([&](int u, int v) {
            res.emplace_back(min(u,v), max(u,v));
        });
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

    Bridges b(n, g);
    vector<pair<int,int>> res = b.all_bridges();
    cout << res.size() << '\n';
    for (auto &[u, v]: res) cout << u + 1 << " " << v + 1 << '\n';
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
