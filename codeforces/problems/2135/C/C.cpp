#include <bits/stdc++.h>
using namespace std;

class dsu {
public:
    int n; vector<int> p;
    vector<int> low;
    vector<bool> odd;
    dsu(int _n) : n(_n), p(_n, -1), low(n, INT_MAX), odd(n, 0) {}

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
    int getlow(int x) {
        return low[set(x)];
    }
    bool getodd(int x) {
        return odd[set(x)];
    }

    void unite(int x, int y) {
        int px = set(x), py = set(y);
        if (px == py) return;
        if (size(px) < size(py)) swap(px, py);
        low[px] = min(low[px], low[py]);
        odd[px] = odd[px] | odd[py];
        p[px] += p[py];
        p[py] = px;
    }
    void updlow(int x, int v) {
        int px = set(x);
        low[px] = min(low[px], v);
    }
    void setodd(int x) {
        int px = set(x);
        odd[px] = true;
    }
};

const int64_t MOD = 998244353;

void solve() {
    int n, m, V;
    cin >> n >> m >> V;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    vector<vector<int>> g(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> vis(n), dep(n);
    dsu d(n);
    function<void(int,int,int,int)> dfs = [&](int u, int p, int c, int curdepth) {
        vis[u] = c;
        dep[u] = curdepth;
        for (int v: g[u]) {
            if (v == p) continue;
            if (!vis[v]) {
                dfs(v, u, 3-c, curdepth+1);
            }
            else if (vis[v] == c) {
                // odd cycle
                d.updlow(u, min(dep[u], dep[v]));
                d.setodd(u);
            }
            else {
                assert(vis[v] != c);
                // even cycle
                d.updlow(u, min(dep[u], dep[v]));
            }
            if (d.getlow(v) <= dep[u]) {
                d.unite(u, v);
            }
        }
    };
    dfs(0, -1, 1, 0);

    vector<vector<int>> ccs(n);
    int64_t ans = 1;
    for (int i = 0; i < n; i++) {
        int p = d.set(i);
        ccs[p].push_back(i);
    }
    for (int i = 0; i < n; i++) {
        if (d.set(i) != i) continue;
        bool isodd = d.getodd(i);

        int64_t cur = isodd ? 1 : V;
        int val = -1;
        // cout << i << ", isOdd: " << boolalpha << isodd << ": ";
        for (int j: ccs[i]) {
            // cout << j << " ";
            if (isodd && a[j] != 0 && a[j] != -1) {
                cur = 0;
            }
            else if (val != -1 && a[j] != -1 && a[j] != val) {
                cur = 0;
            }
            if (a[j] != -1) {
                val = a[j];
            }
        }
        // cout << endl;
        if (val != -1 && cur == V) {
            cur = 1;
        }
        ans *= cur;
        ans %= MOD;
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
