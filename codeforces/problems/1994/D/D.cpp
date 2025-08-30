#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;

    vector<vector<int>> g(n);
    auto get = [&](int x) -> pair<int,int> {
        vector<int> vis(n);
        function<void(int)> dfs = [&](int u) {
            vis[u] = true;
            for (int v: g[u]) {
                if (!vis[v]) dfs(v);
            }
        };
        vector<int> id(x, -1);
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                dfs(i);
                if (id[a[i] % x] != -1) return {id[a[i] % x], i};
                id[a[i] % x] = i;
            }
        }
        exit(1);
    };

    vector<pair<int,int>> ans;
    cout << "YES\n";
    for (int i = n - 1; i >= 1; i--) {
        auto [u, v] = get(i);
        g[u].push_back(v);
        g[v].push_back(u);
        ans.emplace_back(u, v);
    }
    reverse(ans.begin(), ans.end());
    for (auto &[u, v]: ans) {
        cout << u + 1 << " " << v + 1 << '\n';
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
