#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> depth(n), stmax(n);
    depth[0] = 0;
    function<void(int,int)> dfs = [&](int u, int p) {
        stmax[u] = depth[u];
        for (int v: g[u]) {
            if (v != p) {
                depth[v] = depth[u] + 1;
                dfs(v, u);
                stmax[u] = max(stmax[u], stmax[v]);
            }
        }
    };
    dfs(0, -1);
    vector<int> d(n + 1);
    for (int i = 0; i < n; i++) {
        int start = depth[i], last = stmax[i];
        d[start]++;
        d[last + 1]--;
    }
    int mx = d[0];
    for (int i = 1; i < n; i++) {
        d[i] += d[i - 1];
        mx = max(mx, d[i]);
    }
    cout << n - mx << '\n';
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
