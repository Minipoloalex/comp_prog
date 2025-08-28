#include <bits/stdc++.h>
using namespace std;

const int MAX_N = int(1e5);

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> vis(n);
    int cc;
    function<void(int)> dfs = [&](int u) {
        cc++;
        vis[u] = true;
        for (int v: g[u]) {
            if (!vis[v]) dfs(v);
        }
    };
    vector<int> sizes;
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            cc = 0;
            dfs(i);
            sizes.push_back(cc);
        }
    }
    bitset<MAX_N> possible;
    for (int sz: sizes) {
        possible |= (possible << sz);
        possible.set(sz - 1);
    }
    string ans = possible.to_string();
    reverse(ans.begin(), ans.end());
    cout << ans.substr(0,n) << '\n';
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
