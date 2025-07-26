#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> par(n);
    function<void(int,int)> dfs = [&](int u, int p) {
        par[u] = p;
        for (int v: g[u]) {
            if (v != p) {
                dfs(v, u);
            }
        }
    };
    // marked: visited during queries, black: already set to black (not the same as s, since we treat s[i] == '0' like a query)
    vector<bool> marked(n), black(n);
    int root = -1;
    int64_t inside_black = 0, outside_black = n;    // white nodes inside the black paths, and outside
    auto set_black = [&](int u) {
        if (black[u]) return;
        black[u] = 1;
        if (marked[u]) {
            inside_black--;
            return;
        }
        marked[u] = 1;
        if (root == -1) {
            root = u;
            dfs(root, -1);
            outside_black--;
            return;
        }

        // u was not marked (so it was "outside black")
        outside_black--;

        int cur = par[u];
        while (!marked[cur]) {  // if it's not marked, then it's definitely white
            inside_black++;
            outside_black--;
            marked[cur] = 1;
            cur = par[cur];
        }
    };
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') set_black(i);
    }
    while (q--) {
        int u;
        cin >> u;
        u--;
        set_black(u);
        int64_t ans = inside_black * outside_black + (outside_black + 1) * outside_black / 2;
        cout << ans << '\n';
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
