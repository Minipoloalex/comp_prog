#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<string> names(n);
    for (auto &s: names) cin >> s;
    bool possible = true;
    vector<vector<int>> g(26);
    for (int i = 1; i < n; i++) {
        int mx = (int) min(names[i].size(), names[i-1].size());
        int j;
        for (j = 0; j < mx; j++) {
            if (names[i][j] != names[i-1][j]) {
                break;
            }
        }
        if (j != mx) {
            int c1 = names[i - 1][j] - 'a', c2 = names[i][j] - 'a';
            g[c1].push_back(c2);
        }
        if (j == mx && names[i-1].size() > names[i].size()) {
            possible = false;
        }
    }
    vector<int> vis(26);
    string ans;
    function<void(int)> dfs = [&](int u) {
        vis[u] = 1;
        for (int v: g[u]) {
            if (!vis[v]) {
                dfs(v);
            }
            else if (vis[v] == 1) {
                possible = false;
            }
        }
        ans += char('a' + u);
        vis[u] = 2;
    };
    for (int i = 0; i < 26 && possible; i++) {
        if (!vis[i]) dfs(i);
    }
    if (!possible) {
        ans = "Impossible";
    }
    else reverse(ans.begin(), ans.end());
    cout << ans << '\n';
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
