#include <bits/stdc++.h>
using namespace std;

/*
 * Usage:
 *  BellmanFord bf;
 *  vector<int64_t> dist;
 *  vector<int> parent, cycle;
 *  bool has_neg = bf.run(n, edges, src, dist, parent, cycle);
 *
 * Inputs:
 *  - n: number of vertices (0..n-1)
 *  - edges: vector<Edge>{a,b,w}, directed edges
 *  - src: source vertex
 *
 * Outputs:
 *  - dist[v]: shortest distance from src (INF if unreachable, -INF if affected by a neg cycle)
 *  - parent[v]: predecessor for path reconstruction
 *  - cycle: one reachable negative cycle (empty if none)
 *  - return value: true if a reachable negative cycle exists
 */
struct Edge {
    int u, v;
    int64_t w;
};

const int64_t INF = int64_t(4e18);

class BellmanFord {
public:
    bool run(int n, const vector<Edge> &E, int src,
             vector<int64_t> &dist, vector<int> &p, vector<int> &cycle) 
    {
        dist.assign(n, INF);
        p.assign(n, -1);
        cycle.clear();
        dist[src] = 0;

        // Bellman-Ford only needs n-1 iterations
        // If there are changes in the n-th iteration: negative cycle exists
        int x = -1;
        for (int i = 0; i < n; i++) {
            x = -1;
            for (auto &e : E) {
                if (dist[e.u] == INF) continue;
                if (dist[e.u] + e.w < dist[e.v]) {
                    dist[e.v] = max(-INF, dist[e.u] + e.w);
                    p[e.v] = e.u;
                    x = e.v;
                }
            }
        }
        if (x == -1) return false;

        // Build negative cycle
        int y = x;
        for (int i = 0; i < n; i++) y = p[y];
        for (int v = y;; v = p[v]) {
            cycle.push_back(v);
            if (v == y && (int)cycle.size() > 1) break;
        }
        reverse(cycle.begin(), cycle.end());

        // OPTIONAL: propagate -INF (affected nodes by negative cycles)
        // O(N + M)

        // Collect vertices that can still relax (on the n-th pass)
        vector<int> bad(n, 0);
        for (auto &e : E) {
            if (dist[e.u] == INF) continue;
            if (dist[e.u] + e.w < dist[e.v]) bad[e.v] = 1;
        }
        vector<vector<int>> adj(n);
        for (auto &e : E) adj[e.u].push_back(e.v);

        // BFS from all bad nodes to mark everything they can reach as -INF
        queue<int> q;
        for (int i = 0; i < n; i++) if (bad[i]) { dist[i] = -INF; q.push(i); }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) if (dist[v] != -INF) { dist[v] = -INF; q.push(v); }
        }
        return true;
    }

    // Reconstruct path src -> t using the parent array
    // Only valid if dist[t] is finite
    vector<int> get_path(int t, const vector<int> &p) {
        vector<int> path;
        for (; t != -1; t = p[t]) path.push_back(t);
        reverse(path.begin(), path.end());
        return path;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        int a, b, x;
        cin >> a >> b >> x;
        a--;b--;
        x = -x;
        edges[i] = Edge{a, b, x};
    }

    vector<int64_t> dist;
    vector<int> parent, cycle;
    BellmanFord bf;
    bool has_neg_cycle = bf.run(n, edges, 0, dist, parent, cycle);

    // a negative cycle that cannot reach N must not be considered
    if (dist[n - 1] == -INF) {
        cout << "-1\n";
    }
    else {
        cout << -dist[n - 1] << '\n';
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
