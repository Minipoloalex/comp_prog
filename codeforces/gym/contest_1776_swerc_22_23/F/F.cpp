#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> ans(m);
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;v--;
        g[u].push_back(i);
        g[v].push_back(i);
    }
    if (m == n * (n - 1) / 2) {
        for (int gidx = 0; gidx < int(g[0].size()) - 1; gidx++) {
            int i = g[0][gidx];
            ans[i] = 1;
        }
        ans[g[0].back()] = 2;
        cout << "3\n";
    }
    else {
        int mn = INT_MAX;
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (int(g[i].size()) < mn) {
                mn = int(g[i].size());
                idx = i;
            }
        }
        for (int i : g[idx]) {
            ans[i] = 1;
        }
        cout << "2\n";
    }
    for (int c: ans) cout << c + 1 << " ";
    cout << '\n';
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
