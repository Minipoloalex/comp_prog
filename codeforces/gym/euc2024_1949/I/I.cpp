#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<array<int,3>> cs(n);
    for (auto &a: cs) {
        for (int i = 0; i < 3; i++) {
            cin >> a[i];
        }
    }
    auto intersect = [&](int i, int j) {
        auto &[xi, yi, ri] = cs[i];
        auto &[xj, yj, rj] = cs[j];
        int xd = xi - xj;
        int yd = yi - yj;
        int r = ri + rj;
        return int64_t(xd) * xd + int64_t(yd) * yd <= int64_t(r) * r;
    };
    vector<vector<int>> g(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (intersect(i, j)) {
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
    }

    vector<int> vis(n, 0);
    array<int, 2> cur = {0, 0};
    function<bool(int, int)> bip = [&](int u, int c) {
        vis[u] = c;
        cur[c - 1]++;
        int nc = 3 - c;
        bool ok = true;
        for (int v: g[u]) {
            if (!vis[v]) {
                ok &= bip(v, nc);
            }
            else if (vis[v] != nc) {
                ok = false;
            }
        }
        return ok;
    };
    bool yes = false;
    for (int i = 0; i < n; i++) {
        cur[0] = cur[1] = 0;
        if (!vis[i] && bip(i, 1)) {
            if (cur[0] != cur[1]) {
                yes = true;
            }
        }
    }
    cout << (yes ? "YES" : "NO") << '\n';
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
