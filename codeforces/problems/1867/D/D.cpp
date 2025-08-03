#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> b(n + 1);
    vector<int> g(n + 1, -1);
    bool ans = true;
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        if (b[i] == i) {
            if (k != 1) ans = false;
        }
        else {
            if (k == 1) ans = false;
            g[i] = b[i];
        }
    }
    vector<int> vis(n + 1, 0);
    int orig = -1;
    int cycle_size = 0;
    bool cycle = false;
    function<void(int)> dfs = [&](int u) {
        vis[u] = 1;
        int v = g[u];
        if (v == -1) exit(1);

        if (vis[v] == 1) {
            orig = v;
            cycle = true;
        }
        else if (!vis[v]) {
            dfs(v);
        }

        if (cycle) {
            cycle_size++;
            if (orig == u) {
                // cout << cycle_size << " ";
                if (cycle_size != k) {
                    ans = false;
                }
                cycle_size = 0;
                cycle = false;
                orig = -1;
            }
        }
        vis[u] = 2;
    };
    if (ans && k > 1) {
        for (int i = 1; i <= n && ans; i++) {
            if (!vis[i]) {
                dfs(i);
            }
        }
    }
    cout << (ans ? "YES" : "NO") << '\n';
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
