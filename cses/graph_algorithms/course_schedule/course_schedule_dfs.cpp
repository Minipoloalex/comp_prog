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
    }
    vector<int> ans, vis(n);
    bool possible = true;
    function<void(int)> dfs = [&](int u) {
        vis[u] = 1;
        for (int v: g[u]) {
            if (vis[v] == 1) {
                possible = false;   
            }
            else if (vis[v] == 0) dfs(v);
        }
        ans.push_back(u);
        vis[u] = 2;
    };
    for (int i = 0; i < n; i++) {
        if (!vis[i]) dfs(i);
    }
    if (!possible) {
        cout << "IMPOSSIBLE\n";
    }
    else {
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
