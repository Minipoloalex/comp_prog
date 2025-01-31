#include <bits/stdc++.h>
using namespace std;

vector<map<int, int>> ms;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> c(n);
        for (auto &x: c) cin >> x;

        vector<vector<int>> g(n, vector<int>());
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--;v--;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        int64_t ans = 0;
        auto get_ans = [&](int u, int p, auto &&self) -> void {
            int best = -1;
            for (int v: g[u]) {
                if (v != p) {
                    self(v, u, self);
                    if (best == -1 || ms[v].size() > ms[best].size()) {
                        best = v;
                    }
                }
            }
            for (int v: g[u]) {
                if (v != p && v != best) {
                    for (auto &[col, cnt]: ms[v]) {
                        if (col != c[u]) {
                            ans += ms[best][col] * 1LL * cnt;
                        }
                        ms[best][col] += cnt;
                    }
                }
            }
            if (best != -1) swap(ms[best], ms[u]);
            ans += ms[u][c[u]];
            ms[u][c[u]] = 1;
        };

        ms.assign(n, {});
        get_ans(0, -1, get_ans);
        cout << ans << '\n';
    }
    return 0;
}
