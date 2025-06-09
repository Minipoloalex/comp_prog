#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        g[a - 1].push_back(b - 1);
    }
    vector<int> vis(n), ans;
    int found = -1;
    bool finish = false;
    function<void(int)> dfs = [&](int u) {
        vis[u] = 1;
        for (int v: g[u]) {
            if (found != -1) break;
            if (!vis[v]) {
                dfs(v);
            }
            else {
                if (vis[v] == 1) {
                    found = v;
                    ans.push_back(v);
                }
            }
        }
        if (finish) return;
        if (found != -1) ans.push_back(u);
        if (found == u) {
            finish = true;
        }
        vis[u] = 2;
    };
    for (int i = 0; i < n && !finish; i++) {
        if (!vis[i]) dfs(i);
    }
    if (!finish) {
        cout << "IMPOSSIBLE\n";
    }
    else {
        cout << ans.size() << '\n';
        reverse(ans.begin(), ans.end());
        for (int a: ans) cout << a + 1 << " ";
        cout << '\n';
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
