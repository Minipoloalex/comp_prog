#include <bits/stdc++.h>
using namespace std;


class dsu {
public:
    int n; vector<int> p;

    dsu(int _n) : n(_n), p(_n, -1) {}

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

    void unite(int x, int y) {
        int px = set(x), py = set(y);
        if (px == py) return;
        if (size(px) < size(py)) swap(px, py);
        p[px] += p[py];
        p[py] = px;
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

vector<edge<int>> mstedges;

template <typename C>
class kruskal {
public:
    int n; vector<edge<C>> edges;
    kruskal(int _n, vector<edge<C>>& _e) : n(_n), edges(_e) {}

    pair<C, bool> mst() {
        sort(edges.begin(), edges.end());
        dsu d(n);
        int added = 0;
        for (auto& e : edges) {
            if (!d.same(e.u, e.v)) {
                mstedges.push_back(e);
                added++;
                d.unite(e.u, e.v);
            }
        }
        return { 0, added == n - 1 };
    }
};
void solve() {
    int n, m;
    cin >> n >> m;
    vector<edge<int>> edges;
    for (int i = 0; i < m; i++) {
        int ui, vi, wi;
        cin >> ui >> vi >> wi;
        ui--;vi--;
        edges.push_back({ui, vi, wi});
    }

    kruskal<int> k(n, edges);
    k.mst();
    int d;
    cin >> d;
    vector<int> regions(d);
    multiset<int> ladders;
    for (auto &ri: regions) {
        cin >> ri;
        ri--;
    }
    for (int di = 0; di < d; di++) {
        int li;
        cin >> li;
        ladders.insert(li);
    }

    vector<vector<pair<int,int>>> g(n);
    for (auto &e: mstedges) {
        g[e.u].emplace_back(e.v, e.cost);
        g[e.v].emplace_back(e.u, e.cost);
    }
    vector<int> mx(n, 0);
    function<void(int,int,int)> dfs = [&](int u, int p, int cur) {
        mx[u] = cur;
        for (auto &[v, w]: g[u]) {
            if (v == p) continue;
            int ncur = max(cur, w);
            dfs(v, u, ncur);
        }
    };
    dfs(0, -1, 0);

    sort(regions.begin(), regions.end(), [&](int r1, int r2) {
        return mx[r1] < mx[r2] || (mx[r1] == mx[r2] && r1 < r2);
    });

    int ans = 0;
    for (auto &r: regions) {
        int val = mx[r];
        auto it = ladders.lower_bound(val);
        if (it == ladders.end()) continue;
        else {
            ans++;
            ladders.erase(it);
        }
    }
    cout << ans << '\n';
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
