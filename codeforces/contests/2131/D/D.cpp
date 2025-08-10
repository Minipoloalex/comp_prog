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
    int cnt_leafs = 0;
    int mx_cnt = 0;
    for (int i = 0; i < n; i++) {
        int cnt_children_leafs = 0;
        for (int v: g[i]) {
            if (g[v].size() == 1) {
                cnt_children_leafs++;
            }
        }
        mx_cnt = max(mx_cnt, cnt_children_leafs);
        cnt_leafs += g[i].size() == 1;
    }
    if (cnt_leafs >= n - 1) {
        cout << "0\n";
    }
    else {
        cout << cnt_leafs - mx_cnt << '\n';
        // cout << cnt_leafs - 1 << '\n';
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
