#include <bits/stdc++.h>
using namespace std;

void solve() {
    int tx, ty, n;
    cin >> tx >> ty >> n;

    using point = array<double, 2>;
    vector<point> a(n);
    for (auto& [x, y] : a) cin >> x >> y;

    auto intersect = [](const point& f, const point& b, const double& r) {
        double dist = hypot(abs(f[0] - b[0]), abs(f[1] - b[1]));
        return dist <= 2 * r;
    };

    auto can = [&] (double r) {
        vector<vector<int>> g(n);

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (intersect(a[i], a[j], r)) {
                    g[i].push_back(j);
                    g[j].push_back(i);
                }
            }
        }

        vector<bool> vis(n);
        for (int i = 0; i < n; i++) {
            if (vis[i]) continue;

            double up = 0, down = 1e12, left = 1e12, right = 0;
            queue<int> q({ i }); vis[i] = 1;

            while (!q.empty()) {
                int u = q.front(); q.pop();
                auto& [x, y] = a[u];

                up = max(up, y + r);
                down = min(down, y - r);
                left = min(left, x - r);
                right = max(right, x + r);

                for (int neigh : g[u]) {
                    if (!vis[neigh]) {
                        vis[neigh] = 1;
                        q.push(neigh);
                    }
                }
            }

            if (up >= ty && down <= 0) return false;
            if (right >= tx && left <= 0) return false;
            if (up >= ty && right >= tx) return false;
            if (down <= 0 && left <= 0) return false;
        }

        return true;
    };

    double l = 0, r = double(min(tx, ty));
    for (int i = 0; i < 60; i++) {
        double m = (l + r) / 2;
        if (can(m)) l = m;
        else r = m;
    }

    cout << fixed << setprecision(8) << l << endl;
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
