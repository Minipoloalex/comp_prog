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
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        p--;
        g[p].push_back(i);
        up[i][0] = p;
    }
    function<void(int,int)> dfs = [&](int u, int p) {   // build binary-lifting table (and depth)
        for (int k = 1; k < LOG; k++) {
            up[u][k] = up[up[u][k-1]][k-1];
        }
        for (int v: g[u]) {
            if (v != p) {
                depth[v] = depth[u] + 1;
                dfs(v, u);
            }
        }
    };
    dfs(0, -1);
    auto jump = [&](int a, int k) { // jump k nodes (helpful for making a and b match depths)
        for (int p = LOG - 1; p >= 0; p--) {    // here, increasing or decreasing order does not make a difference
            if ((1 << p) & k) {
                a = up[a][p];
            }
        }
        return a;
    };
    auto lca = [&](int a, int b) {
        if (depth[a] < depth[b]) swap(a,b);
        // depth[a] >= depth[b]

        a = jump(a, depth[a] - depth[b]);   // make a and b match depths
        if (a == b) return a;

        for (int p = LOG - 1; p >= 0; p--) {    // in decreasing order, we go to new nodes if they're not the same
            if (up[a][p] != up[b][p]) {
                a = up[a][p];
                b = up[b][p];
            }
        }
        return up[a][0];
    };
    while (q--) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        cout << lca(a, b) + 1 << '\n';   
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
