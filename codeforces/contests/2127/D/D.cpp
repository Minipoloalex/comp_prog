#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = int(1e9) + 7;
const int MAX = int(2e5);

int64_t fact[MAX + 1];

void precompute_facts() {   // requires setting MAX and MOD
    fact[0] = 1;
    for (int i = 1; i <= MAX; i++) {
        fact[i] = (i * fact[i - 1]) % MOD;
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> vis(n);
    function<pair<int64_t,int>(int, int, int)> dfs = [&](int u, int c, int p) -> pair<int64_t,int> {
        vis[u] = c;
        int64_t ansu = 1;
        // int sz = int(g[u].size());
        int cnt_children_have_one = 0;
        int cnt_children_not_one = 0;
        int cc_depth = 0;
        int nc = 3 - c;
        for (int v: g[u]) {
            if (g[v].size() == 1) {
                cnt_children_have_one++;
            }
            else {
                cnt_children_not_one++;
            }

            if (!vis[v]) {
                auto [ansv, res_cc_dep] = dfs(v, nc, u);
                cc_depth = max(cc_depth, res_cc_dep + 1);
                ansu = ansu * ansv % MOD;
            }
            else if (vis[v] == c) {
                ansu = 0;
            }
            else {
                // make sure you came from it, otherwise it's not a tree
                assert(vis[v] == nc);
                if (v != p) {
                    ansu = 0;
                }
            }
        }
        ansu = ansu * fact[cnt_children_have_one] % MOD;
        if (cnt_children_not_one > 2) {
            return {0, 0};
        }
        return {ansu, cc_depth};
    };
    vector<int> cand(n);
    iota(cand.begin(), cand.end(), 0);
    sort(cand.rbegin(), cand.rend(), [&](int i, int j) {
        return g[i].size() < g[j].size();
    });

    auto [ans, cc_depth] = dfs(cand[0], 1, -1);
    ans *= 2;
    if (cc_depth >= 2) ans *= 2;
    ans = ans % MOD;
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    precompute_facts();
    while (t--) {
        solve();
    }
    return 0;
}
