#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (auto &ai: arr) cin >> ai;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<set<int>> colors(n);
    vector<int> ans(n);
    function<void(int,int)> dfs = [&](int u, int p) {
        colors[u].insert(arr[u]);
        for (int v: g[u]) {
            if (v != p) {
                dfs(v, u);
                if (colors[u].size() < colors[v].size()) {
                    swap(colors[u], colors[v]);
                }
                for (int color: colors[v]) {
                    colors[u].insert(color);
                }
            }
        }
        ans[u] = int(colors[u].size());
    };
    dfs(0, -1);
    for (int v: ans) cout << v << " ";
    cout << '\n';
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
