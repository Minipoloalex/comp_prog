#include <bits/stdc++.h>
using namespace std;

class ufds {
    int n;
    vector<int> rnk, p;
public:
    ufds(int sz) {
        n = sz;
        rnk.assign(n, 1);
        p.resize(n);
        iota(p.begin(), p.end(), 0);
    }
    int get(int a) {
        return p[a] = (p[a] == a ? a : get(p[a]));
    }
    bool same_set(int a, int b) {
        return get(a) == get(b);
    }
    void unite(int a, int b) {
        int pa = p[a];
        int pb = p[b];
        if (pa == pb) return;
        if (rnk[pa] < rnk[pb]) swap(pa, pb);
        p[pb] = pa;
        if (rnk[pa] == rnk[pb]) rnk[pa]++;
    }
};


void solve() {
    int n;
    cin >> n;
    vector<vector<int64_t>> d(n, vector<int64_t>(n));
    vector<tuple<int,int,int>> e;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> d[i][j];
            if (d[i][j] != 0) {
                e.emplace_back(d[i][j], i, j);
            }
        }
    }
    sort(e.begin(), e.end());
    vector<vector<pair<int,int>>> g(n);
    ufds dsu(n);
    int edges = 0;
    for (auto &[w, i, j]: e) {
        if (!dsu.same_set(i, j)) {
            dsu.unite(i, j);
            g[i].emplace_back(j, w);
            g[j].emplace_back(i, w);
            edges++;
        }
    }
    vector<vector<int64_t>> dist(n, vector<int64_t>(n));
    function<void(int,int,int)> dfs = [&](int s, int u, int p) {
        for (auto &[v, w]: g[u]) {
            if (v != p) {
                dist[s][v] = dist[s][u] + w;    // could overflow here if using ints
                dfs(s, v, u);
            }
        }
    };
    bool ans;
    if (edges == n - 1) {
        for (int i = 0; i < n; i++) {
            dfs(i, i, -1);
        }
        ans = d == dist;
    }
    else ans = false;
    cout << (ans ? "YES" : "NO") << '\n';
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
