#include <bits/stdc++.h>
using namespace std;

int n;
vector<tuple<int,int,int>> cows;
vector<int> vis;

int distance_sq(int x1, int y1, int x2, int y2) {
    int yd = y2 - y1;
    int xd = x2 - x1;
    return yd * yd + xd * xd;
}

bool possible(int u, int v) {
    auto &[xu, yu, pu] = cows[u];
    auto &[xv, yv, _] = cows[v];

    return distance_sq(xu, yu, xv, yv) <= pu * pu;
}
int dfs(int u) {
    vis[u] = 1;
    int ans = 1;
    for (int v = 0; v < n; v++) {
        if (!vis[v] && possible(u, v)) {
            ans += dfs(v);
        }
    }
    return ans;
}

void solve() {
    freopen("moocast.in", "r", stdin);
    freopen("moocast.out", "w", stdout);
    cin >> n;
    cows.resize(n);
    for (auto &[x, y, p]: cows) cin >> x >> y >> p;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        vis.assign(n, 0);
        ans = max(ans, dfs(i));
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
