#include <bits/stdc++.h>
using namespace std;

#include <bits/stdc++.h>
using namespace std;

class dinic {
    using T = int64_t;
public:
    const T inf = numeric_limits<T>::max();
    T lim = 1;
    struct edge {
        int to; T flow, cap;
        edge(int _t, T _f, T _c) : to(_t), flow(_f), cap(_c) {};
    };
    int n, s, t; // number of nodes, source, sink
    vector<edge> edges; // edge list for xor trick
    vector<vector<int>> g; // adj list but indices point to edges on the edge list
    vector<int> lvl, next; // level graph, next for dfs otimization

    bool sp() {
        lvl.assign(n, -1); lvl[s] = 0;
        queue<int> q({ s });
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == t) return true;
            for (int idx : g[u]) {
                edge& e = edges[idx];
                if (lvl[e.to] != -1 || e.cap - e.flow < lim) continue;
                if (e.flow < e.cap) { lvl[e.to] = lvl[u] + 1; q.push(e.to); }
            }
        }
        return false;
    }

    T dfs(int u, T pushed) {
        if (u == t) return pushed;
        for (; next[u] < (int) g[u].size(); next[u]++) {
            edge& e = edges[g[u][next[u]]];
            edge& rev = edges[g[u][next[u]] ^ 1];
            if (lvl[u] + 1 != lvl[e.to] || e.cap - e.flow == 0) continue;
            T nf = dfs(e.to, min(pushed, e.cap - e.flow));
            if (nf == 0) continue;
            e.flow += nf;
            rev.flow -= nf;
            return nf;
        }
        return 0;
    }

    dinic(int N) : n(N), s(0), t(N - 1), g(N), lvl(N), next(N) {}

    void add_edge(int u, int v, T cap) {
        int idx = (int) edges.size();
        g[u].push_back(idx); edges.emplace_back(v, 0, cap);
        g[v].push_back(idx + 1); edges.emplace_back(u, 0, 0);
    }

    T max_flow() {
        T f = 0;
        // (scaling) wrap while in: for (lim = inf; lim > 0; lim >>= 1)
        while (sp()) {
            next.assign(n, 0);
            while (T pushed = dfs(s, inf)) f += pushed;
        }
        return f;
    }
};


void solve() {
    const int64_t inf = 1e9;
    int n; cin >> n;

    const int src = 0, sink = n + 1;
    dinic mf(n + 2);
    mf.add_edge(src, 1, inf);

    int64_t ans = 0;
    for (int i = 1; i <= n; i++) {
        string s; cin >> s;

        if (s == "*") {
            int to; cin >> to;
            if (to == 1) mf.add_edge(i, sink, inf);
            else mf.add_edge(i, to, inf);
        } else {
            int k = stoi(s);
            vector<int> edges(n + 1);
            for (int j = 0; j < k; j++) {
                int to; cin >> to;
                edges[to]++;
            }

            for (int j = 1; j <= n; j++) {
                if (edges[j] == 0) continue;

                if (j == 1) {
                    if (i == 1) ans += edges[1];
                    else mf.add_edge(i, sink, edges[1]);
                } else {
                    mf.add_edge(i, j, edges[j]);
                }
            }
        }
    }

    int64_t flow = mf.max_flow();
    ans += flow + 1;

    if (ans >= inf) cout << "*\n";
    else cout << ans << '\n';
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
