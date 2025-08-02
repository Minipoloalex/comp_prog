#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> c(n);
    for (auto &ci: c) cin >> ci;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        x--;y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    vector<int64_t> ans(n);
    vector<map<int,int64_t>> sums(n);   // frequency to sum of colors
    vector<map<int,int>> freqs(n); // color to frequency
    function<void(int,int)> dfs = [&](int u, int p) {
        sums[u][1] = c[u];
        freqs[u][c[u]] = 1;
        for (int v: g[u]) {
            if (v != p) {
                dfs(v, u);
                if (freqs[u].size() < freqs[v].size()) {
                    swap(sums[u], sums[v]);
                    swap(freqs[u], freqs[v]);
                }
                // merge v's structures onto u's
                for (auto &[color, f]: freqs[v]) {
                    int old_fu = freqs[u][color];
                    int new_fu = old_fu + f;

                    sums[u][old_fu] -= color;
                    sums[u][new_fu] += color;
                    freqs[u][color] = new_fu;
                }
            }
        }
        ans[u] = sums[u].rbegin()->second;
    };
    dfs(0, -1);
    for (int64_t v: ans) {
        cout << v << " ";
    }
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
