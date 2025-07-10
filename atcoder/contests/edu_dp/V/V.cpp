#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    int64_t m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<int64_t> down(n), dp(n); // down: subtree values

    // we can't do mod division because MOD is not prime
    // We need to use prefix and suffix products to avoid having to do modular division
    vector<vector<int>> children(n);
    vector<int> child_id(n);

    // no explicit dp needed (can just be dfs, since color = white: ans = 1)
    function<void(int,int)> dfs_subtree = [&](int u, int p) {  // aka dfs_subtree
        int64_t cur = 1;
        for (int v: g[u]) {
            if (v != p) {
                child_id[v] = int(children[u].size());
                children[u].push_back(v);
                dfs_subtree(v, u);
                (cur *= (down[v] + 1)) %= m;
            }
        }
        down[u] = cur;
    };
    dfs_subtree(0, -1);

    // values for prefix and suffix of products (assume i is black)
    vector<vector<int64_t>> pref(n), suf(n);
    for (int i = 0; i < n; i++) {
        pref[i].resize(children[i].size() + 1, 1);
        suf[i].resize(children[i].size() + 1, 1);
        for (int j = 0; j < int(children[i].size()); j++) {
            int c = children[i][j];
            (pref[i][j + 1] = pref[i][j] * (down[c] + 1)) %= m;
        }
        for (int j = int(children[i].size()) - 1; j >= 0; j--) {
            int c = children[i][j];
            (suf[i][j] = suf[i][j + 1] * (down[c] + 1)) %= m;
        }
    }
    auto get_down_excluding_child = [&](int src, int dst) {
        int idx = child_id[dst];
        // pref[idx]: non-inclusive so won't include u's value
        // suf[idx]: includes [idx, n - 1], so needs idx + 1
        return (pref[src][idx] * suf[src][idx + 1]) % m;
    };
    function<void(int,int,int64_t)> dfs = [&](int src, int parent, int64_t cur_value) {
        dp[src] = (down[src] * cur_value) % m;
        for (int dst: g[src]) {
            if (dst != parent) {
                // src is black: cur_value * get_down_excluding_child(src, dst)
                // src is white: 1
                int64_t new_cur_value = (cur_value * get_down_excluding_child(src, dst) + 1) % m;
                dfs(dst, src, new_cur_value);
            }
        }
    };
    dfs(0, -1, 1);
    for (int i = 0; i < n; i++) {
        cout << dp[i] << '\n';
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
