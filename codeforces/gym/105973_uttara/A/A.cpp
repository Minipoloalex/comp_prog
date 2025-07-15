#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<array<int, 2>>> g(n);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u-1].push_back({w, v-1});
        g[v-1].push_back({w, u - 1});
    }

    for (auto& v : g) sort(v.begin(), v.end());

    vector<int> a(n, 1);
    for (int i = 0; i < n; i++) {
        if (g[i].empty()) continue;
        a[i] = g[i][0][0];
    }

    bool can = true;

    for (int i = 0; i < n; i++) {
        for (auto& [w, nei] : g[i]) {
            int mx = max(a[i], a[nei]);
            if (mx != w) can = false;
        }
    }

    if (can) {
        for (int i = 0; i < n; i++) 
            cout << a[i] << " \n"[i == n-1];
    } else {
        cout << "-1\n";
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
