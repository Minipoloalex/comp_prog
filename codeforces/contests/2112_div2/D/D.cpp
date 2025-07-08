#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int idx = -1;
    for (int i = 0; i < n; i++) {
        int gs = int(g[i].size());
        if (gs == 1) idx = i;   // facilitates me
    }
    bool ans = false;
    vector<pair<int,int>> e;
    function<void(int,int,int)> dfs = [&](int u, int p, int c) {
        for (int v: g[u]) {
            if (v != p) {
                int nc = 1 - c;
                if (!ans && g[u].size() == 2) {
                    ans = true;
                    nc = c; // don't flip here actually
                }
                if (nc == 1) {
                    e.emplace_back(v, u);
                }
                else {
                    e.emplace_back(u, v);
                }
                dfs(v, u, nc);
            }
        }
    };
    dfs(idx, -1, 1);
    if (ans) {
        cout << "YES\n";
        for (auto &[u, v]: e) {
            cout << u + 1 << " " << v + 1 << '\n';
        }
    }
    else {
        cout << "NO\n";
    }
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
