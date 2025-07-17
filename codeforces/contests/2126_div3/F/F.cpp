#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    vector<pair<int,int64_t>> par(n);
    vector<vector<pair<int,int64_t>>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        u--;v--;
        g[u].emplace_back(v, c);
        g[v].emplace_back(u, c);
    }
    vector<map<int,int64_t>> mp(n);
    int64_t ans = 0;
    function<void(int,int,int64_t)> dfs = [&](int u, int p, int64_t prevcost) {
        par[u] = {p, prevcost};
        for (auto &[v, cost]: g[u]) {
            if (v != p) {
                if (a[u] != a[v]) ans += cost;
                mp[u][a[v]] += cost;
                dfs(v, u, cost);
            }
        }
    };
    dfs(0, -1, -1);

    while (q--) {
        int v, x;
        cin >> v >> x;
        v--;
        int old_color = a[v];
        int new_color = x;
        a[v] = x;

        ans += mp[v][old_color];
        ans -= mp[v][new_color];

        auto &[parent, cost] = par[v];
        if (parent != -1) {
            mp[parent][old_color] -= cost;
            mp[parent][new_color] += cost;
            if (old_color == a[parent]) {
                ans += cost;
            }
            if (new_color == a[parent]) {
                ans -= cost;
            }
        }
        cout << ans << '\n';
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
