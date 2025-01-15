#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> g;
vector<char> milk;
vector<int> vis;
void dfs(int u, int cc_id) {
    vis[u] = cc_id;
    char cu = milk[u];
    for (int v: g[u]) {
        if (!vis[v] && milk[v] == cu) {
            dfs(v, cc_id);
        }
    }
}
void solve() {
    int n, m;
    cin >> n >> m;
    milk.resize(n);
    g.assign(n, {});
    vis.assign(n, 0);
    for (auto &x: milk) cin >> x;
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        x--;y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    int cc_id = 1;
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(i, cc_id++);
        }
    }
    while (m--) {
        int ai, bi;
        char ci;
        cin >> ai >> bi >> ci;
        ai--;bi--;
        int ans = 1;
        int cca = vis[ai];
        int ccb = vis[bi];
        if (cca == ccb) {
            // both in same
            ans = milk[ai] == ci;   // same as milk[bi] == ci
        }
        cout << ans;
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    freopen("milkvisits.in", "r", stdin);
    freopen("milkvisits.out", "w", stdout);
    solve();
    return 0;
}
