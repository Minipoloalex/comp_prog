#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int64_t> a(n);
    for (auto &ai: a) cin >> ai;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int64_t> mn(n, INT64_MAX), mx(n, INT64_MIN);

    function<void(int,int)> dfs = [&](int u, int p) {
        mn[u] = mx[u] = a[u];
        if (p != -1) {
            mn[u] = min(mn[u], mn[u] - mx[p]);
            mx[u] = max(mx[u], mx[u] - mn[p]);
        }
        for (int v: g[u]) {
            if (v != p) {
                dfs(v, u);
            }
        }
    };
    dfs(0, -1);
    for (int64_t val: mx) cout << val << " ";
    cout << '\n';
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
