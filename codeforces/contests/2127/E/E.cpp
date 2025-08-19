#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int64_t> w(n);
    for (auto &wi: w) cin >> wi;
    vector<int> c(n);
    for (auto &ci: c) cin >> ci;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    if (all_of(c.begin(), c.end(), [](int color) { return color == 0; })) {
        // means all colors are 0
        cout << "0\n";
        for (int i = 0; i < n; i++) {
            cout << "1 ";
        }
        cout << '\n';
        return;
    }

    function<void(int,int,int)> dfs_assign = [&](int u, int p, int color) {
        c[u] = color;
        for (int v: g[u]) {
            if (v != p) {
                dfs_assign(v, u, color);
            }
        }
    };

    vector<set<int>> cs(n);
    int64_t ans = 0;
    function<void(int,int,int)> dfs = [&](int u, int p, int closest_parent_color) {
        if (c[u] != 0) {
            closest_parent_color = c[u];
        }
        bool counted = false;
        vector<int> needassign;
        for (int v: g[u]) {
            if (v != p) {
                dfs(v, u, closest_parent_color);
                if (cs[v].empty()) {
                    // save as children to assign color
                    needassign.push_back(v);
                }
                else {
                    if (cs[u].size() < cs[v].size()) {
                        swap(cs[u], cs[v]);
                    }
                    for (int color: cs[v]) {
                        auto [_, inserted] = cs[u].insert(color);
                        if (!inserted) {
                            // means we had a color collision between children
                            if (c[u] == 0) {
                                c[u] = color;
                            }
                            else {
                                if (c[u] != color && !counted) {
                                    ans += w[u];
                                    counted = true;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (!cs[u].empty() && c[u] == 0) {
            // a parent with no repeated colors (in children): just assign any of its colors
            c[u] = *cs[u].begin();
        }

        if (c[u] != 0) {
            // it's only 0 if all children have no color
            cs[u].insert(c[u]);
            for (int v: needassign) {
                dfs_assign(v, u, c[u]);
            }
        }
    };

    dfs(0, -1, 0);
    cout << ans << '\n';
    for (int ci: c) {
        assert(ci != 0);
        cout << ci << " ";
    }
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
