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
    vector<int> dep(n);
    function<void(int,int,int)> dfs = [&](int u, int p, int d) {
        dep[u] = d;
        for (int v: g[u]) {
            if (v != p) {
                dfs(v, u, d + 1);
            }
        }
    };
    dfs(n-1, -1, 0);

    bool cur_dep_parity = dep[0] % 2;
    vector<int> nodes(n);
    iota(nodes.begin(), nodes.end(), 0);
    sort(nodes.begin(), nodes.end(), [&](int u, int v) {
        return dep[u] > dep[v];
    });
    vector<pair<int,int>> ans; ans.reserve(3*n);
    for (int i = 0; i < n-1; i++) {
        int cur = nodes[i];
        if (dep[cur] % 2 == cur_dep_parity) {
            ans.emplace_back(1,-1);
            cur_dep_parity ^= 1;
        }
        ans.emplace_back(2, cur);
        ans.emplace_back(1,-1);
        cur_dep_parity ^= 1;
    }
    cout << ans.size() << '\n';
    for (auto &[type, u]: ans) {
        cout << type;
        if (type == 2) {
            cout << " " << u+1;
        }
        cout << '\n';
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
