#include <bits/stdc++.h>
using namespace std;

const int LOG = 20;
const int MAXN = int(2e5);

int up[MAXN][LOG];

void solve() {
    int n, q;
    cin >> n >> q;
    vector<vector<int>> g(n);
    vector<int> depth(n, 0);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    function<void(int,int)> DFS = [&](int u, int p) {
        if (p != -1) up[u][0] = p;
        for (int j = 1; j < LOG; j++) {
            up[u][j] = up[up[u][j-1]][j-1];
        }
        for (int v: g[u]) {
            if (v != p) {
                depth[v] = depth[u] + 1;
                DFS(v, u);
            }
        }
    };
    auto JUMP = [&](int a, int k) {
        for (int p = 0; p < LOG; p++) {
            if ((1 << p) & k) {
                a = up[a][p];
            }
        }
        return a;
    };
    auto LCA = [&](int a, int b) {
        if (depth[a] < depth[b]) swap(a,b);
        a = JUMP(a, depth[a] - depth[b]);
        if (a == b) return a;
        for (int p = LOG - 1; p >= 0; p--) {
            if (up[a][p] != up[b][p]) {
                a = up[a][p];
                b = up[b][p];
            }
        }
        return up[a][0];
    };
    // we can select the root arbitrarily
    DFS(0, -1);
    while (q--) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        int lca = LCA(a, b);
        int total_dist = depth[a] + depth[b] - 2 * depth[lca];
        cout << total_dist << '\n';
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
