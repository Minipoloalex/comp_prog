#include <bits/stdc++.h>
using namespace std;

class mcmf {
    using F = int64_t;
    using C = int64_t;
public:
    constexpr static F infF = numeric_limits<F>::max() / 2;
    constexpr static C infC = numeric_limits<C>::max() / 2;
    struct edge {
        int to; F flow, cap; C cost;
        edge(int _t, F _f, F _c, C _cs) : to(_t), flow(_f), cap(_c), cost(_cs) {}
    };
    int n, s, t;
    vector<edge> edges;
    vector<vector<int>> g; // index to edge list
    vector<int> par; // edge idx that is parent in sp
    vector<C> p; // potentials
    vector<F> f; // flow that reached a node

    bool sp() {
        vector<C> ds(n, infC);
        vector<bool> vis(n, 0);
        priority_queue<pair<C, int>, vector<pair<C, int>>, greater<>> pq;
        pq.emplace(0, s);
        ds[s] = 0; f[s] = infF;
        while (!pq.empty()) {
            auto [c, u] = pq.top();
            pq.pop();
            vis[u] = 1;
            for (int idx : g[u]) {
                edge& e = edges[idx];
                if (vis[e.to]) continue;
                C d = ds[u] + p[u] - p[e.to] + e.cost;
                if (e.flow < e.cap && d < ds[e.to]) {
                    ds[e.to] = d;
                    par[e.to] = idx;
                    f[e.to] = min(f[u], e.cap - e.flow);
                    pq.emplace(ds[e.to], e.to);
                }
            }
        }
        for (int i = 0; i < n; i++) p[i] = min(p[i] + ds[i], infC);
        return vis[t];
    }

    F push(F k) {
        for (int cur = t; cur != s; cur = edges[par[cur] ^ 1].to) {
            edges[par[cur]].flow += k;
            edges[par[cur] ^ 1].flow -= k;
        }
        return k;
    }

    mcmf(int N) : n(N), s(0), t(N - 1), g(N), par(N), p(N), f(N) {}

    void add_edge(int u, int v, F cap, C cost) {
        int idx = (int) edges.size();
        g[u].push_back(idx); edges.emplace_back(v, 0, cap, cost);
        g[v].push_back(idx + 1); edges.emplace_back(u, 0, 0, -cost);
    }

    void potentials() { // call this before max_flow
        fill(p.begin(), p.end(), infC);
        p[s] = 0;
        int it = n, ch = 1;
        while (ch-- && it--)
            for (int i = 0; i < n; i++)
                if (p[i] != infC)
                    for (int idx : g[i]) {
                        edge& e = edges[idx];
                        C cost = p[i] + e.cost;
                        if (e.cap && cost < p[e.to]) p[e.to] = cost, ch = 1;
                    }
        assert(it >= 0); // assert no negative cycle
    }

    pair<F, C> max_flow(F k = infF) {
        F fl = 0; while (sp() && fl != k) fl += push(min(k - fl, f[t]));
        C c = 0; for (auto& e : edges) c += int(e.flow > 0) * e.flow * e.cost;
        return { fl, c };
    }
};

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    mcmf flow(n);
    while (m--) {
        int a, b, r, c;
        cin >> a >> b >> r >> c;
        a--;b--;
        flow.add_edge(a, b, r, c);
    }

    // I think this is the O(V*E) handling of negative costs (not needed here)
    // which (obviously) doesn't support negative cycles
    // flow.potentials();

    auto [f, cost] = flow.max_flow(k);

    if (f == k) {
        cout << cost << '\n';
    }
    else {
        cout << "-1\n";
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
