#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<int> vis(n), ans;
    int found = -1;
    bool finish = false;
    function<void(int,int)> dfs = [&](int u, int p) {
        vis[u] = 1;
        for (int v: g[u]) {
            if (found != -1) break;
            if (v == p) continue;

            if (!vis[v]) {
                dfs(v,u);
            }
            else {
                found = v;
                ans.push_back(v);
            }
        }
        if (finish) return;

        if (found != -1) ans.push_back(u);
        if (found == u) {
            finish = true;
        }
    };
    for (int i = 0; i < n && !finish; i++) {
        if (!vis[i]) dfs(i,-1);
    }

    if (!finish) {
        cout << "IMPOSSIBLE\n";
    }
    else {
        cout << ans.size() << '\n';
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
