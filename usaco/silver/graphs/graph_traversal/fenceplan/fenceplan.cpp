#include <bits/stdc++.h>
using namespace std;

vector<int> vis;
vector<vector<int>> g;
vector<pair<int,int>> cows;

void dfs(int u, vector<int> &cc) {
    vis[u] = 1;
    cc.push_back(u);
    for (int v: g[u]) {
        if (!vis[v]) {
            dfs(v, cc);
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    cows.resize(n);
    g.assign(n, vector<int>());
    for (auto &[x, y]: cows) cin >> x >> y;
    while (m--) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vis.assign(n, 0);
    int ans = INT_MAX;  // 4e8 is actual max
    for (int i = 0; i < n; i++) {
        if (vis[i]) continue;
        vector<int> cc;

        dfs(i, cc);
        pair<int,int> x{INT_MAX, 0}, y{INT_MAX, 0};
        for (int c: cc) {
            auto &[xc, yc] = cows[c];
            x.first = min(x.first, xc);
            x.second = max(x.second, xc);
            y.first = min(y.first, yc);
            y.second = max(y.second, yc);
        }
        int xd = x.second - x.first;
        int yd = y.second - y.first;
        ans = min(ans, 2 * xd + 2 * yd);
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    freopen("fenceplan.in", "r", stdin);
    freopen("fenceplan.out", "w", stdout);
    solve();
    return 0;
}
