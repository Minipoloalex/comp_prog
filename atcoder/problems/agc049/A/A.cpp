#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<string> g(n);
    for (auto &s: g) cin >> s;
    vector<int> reached_by(n, 0), vis(n, 0);
    function<int(int)> revdfs = [&](int u) {
        int ans = 1;
        vis[u] = true;
        for (int v = 0; v < n; v++) {
            if (g[v][u] == '1' && !vis[v]) {
                ans += revdfs(v);
            }
        }
        return ans;
    };
    for (int i = 0; i < n; i++) {
        vis.assign(n, 0);
        reached_by[i] = revdfs(i);
    }
    double ans = 0;
    for (int i = 0; i < n; i++) {
        ans += 1.0 / reached_by[i];
    }
    cout << fixed << setprecision(9) << ans << '\n';
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
