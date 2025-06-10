#include <bits/stdc++.h>
using namespace std;

// simple Minimum Spanning Tree (MST) implementations

const int64_t INF = int64_t(1e18);
int64_t prim(int n, vector<vector<pair<int,int>>> &g) {
    vector<int64_t> d(n, INF);
    vector<int> vis(n);
    set<pair<int64_t,int>> pq;
    d[0] = 0;
    pq.emplace(0, 0);
    int64_t ans = 0;
    while (!pq.empty()) {
        auto [dist, u] = *pq.begin();
        vis[u] = 1;
        ans += dist;
        pq.erase(pq.begin());
        for (auto &[v, w]: g[u]) {
            if (!vis[v] && w < d[v]) {
                pq.erase({d[v], v});
                d[v] = w;
                pq.emplace(d[v], v);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (d[i] == INF) {
            return -1;
        }
    }
    return ans;
}

class dsu {
    int n;
    vector<int> p, rnk;
public:
    dsu(int sz) {
        n = sz;
        p.resize(n);
        iota(p.begin(), p.end(), 0);
        rnk.assign(n, 1);
    }
    int get(int a) {
        return p[a] = (p[a] == a ? a : get(p[a]));
    }
    int same_set(int a, int b) {
        return get(a) == get(b);
    }
    void unite(int a, int b) {
        int pa = get(a);
        int pb = get(b);
        if (pa == pb) return;

        if (rnk[pa] < rnk[pb]) swap(pa, pb);
        p[pb] = pa;
        if (rnk[pa] == rnk[pb]) rnk[pa]++;
    }
};

int64_t kruskal(int n, vector<vector<pair<int,int>>> &g) {
    dsu d(n);
    vector<tuple<int,int,int>> e;   // usually, we would build this as we read the edges, but here we'll do this
    for (int i = 0; i < n; i++) {
        for (auto &[j, w]: g[i]) {
            e.emplace_back(w,i,j);
        }
    }
    sort(e.begin(), e.end());
    int64_t ans = 0;
    for (auto &[w, i, j]: e) {
        if (!d.same_set(i, j)) {
            d.unite(i, j);
            ans += w;
        }
    }
    for (int i = 0; i < n; i++) {
        if (!d.same_set(0, i)) {    // could check instead by how many edges we use (should be n - 1)
            return -1;
        }
    }
    return ans;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int,int>>> g(n);
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;b--;
        g[a].emplace_back(b, c);
        g[b].emplace_back(a, c);
    }
    // int64_t ans = prim(n, g);
    int64_t ans = kruskal(n, g);
    if (ans == -1) {
        cout << "IMPOSSIBLE\n";
    }
    else {
        cout << ans << '\n';
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
