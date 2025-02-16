#include <bits/stdc++.h>
using namespace std;

struct edge {
    int from, to;
    int64_t cost;
    edge(int _f, int _t, int64_t _c): from(_f), to(_t), cost(_c) {};
    bool operator <(const edge& o) const {
        if (cost == o.cost) return from < o.from;
        return cost < o.cost;
    }
};

class dsu {
    vector<int> parent;
public:
    dsu(int n) { parent.resize(n); iota(parent.begin(), parent.end(), 0); }
    int set(int x) {
        return parent[x] = (x == parent[x] ? x : set(parent[x]));
    }
    bool same_set(int x, int y) {
        return set(x) == set(y);
    }
    void unite(int x, int y) {
        if (same_set(x, y)) return;
        int px = set(x);
        int py = set(y);
        parent[py] = px;
    }
};

void solve() {
    int n; cin >> n;
    vector<vector<int64_t>> m(n, vector<int64_t>(n));
    vector<int64_t> p(n);
    vector<edge> edges;
    edges.reserve(n * n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> m[i][j];
            if (i != j) {
                edges.emplace_back(i, j, m[i][j]);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        edges.emplace_back(n, i, m[i][i]);
    }

    sort(edges.begin(), edges.end());
    dsu d(n + 1);
    int64_t ans = 0;
    for (edge e: edges) {
        if (d.same_set(e.to, e.from)) continue;
        ans += e.cost;
        d.unite(e.to, e.from);
    }
    cout << ans << endl;
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
