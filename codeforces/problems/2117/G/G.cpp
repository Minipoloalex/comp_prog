#include <bits/stdc++.h>
using namespace std;

class dsu {
public:
    int n; vector<int> p, mn, mx;

    dsu(int _n) : n(_n), p(_n, -1), mn(n, INT_MAX), mx(n, INT_MIN) {}

    int set(int x) {
        if (p[x] < 0) return x;
        return p[x] = set(p[x]);
    }

    bool same(int x, int y) {
        return set(x) == set(y);
    }

    int size(int x) {
        return -p[set(x)];
    }

    void unite(int x, int y, int cost) {
        int px = set(x), py = set(y);
        
        if (px == py) return;
        if (size(px) < size(py)) swap(px, py);
        
        mn[px] = min({mn[px], mn[py], cost});
        mx[px] = max({mx[px], mx[py], cost});

        p[px] += p[py];
        p[py] = px;
    }
    int get_value(int x) {
        return mx[set(x)] + mn[set(x)];
    }
};

template <typename C>
class edge {
public:
    int u, v; C cost;

    bool operator <(const edge& o) const {
        return cost < o.cost;
    }
};

template <typename C>
class kruskal {
public:
    int n; vector<edge<C>> edges;
    kruskal(int _n, vector<edge<C>>& _e) : n(_n), edges(_e) {}

    int solve() {
        sort(edges.begin(), edges.end());
        dsu d(n);
        int ans = INT_MAX;
        for (auto& e : edges) {
            d.unite(e.u, e.v, e.cost);
            if (d.same(0, n - 1)) {
                ans = min(ans, d.get_value(0));
            }
        }
        return ans;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<edge<int>> edges(m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;v--;
        edges[i] = {u, v, w};
    }
    kruskal<int> k(n, edges);
    int ans = k.solve();
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
