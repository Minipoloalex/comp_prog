#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    int a, b;
    cin >> a >> b;
    a--;b--;
    vector<vector<int>> g(n);
    vector<int> dista(n, -1), distb(n, -1);
    function<void(int,int,vector<int>&)> dfs1 = [&](int u, int p, vector<int> &dist) {
        if (p == -1) dist[u] = 0;
        else dist[u] = dist[p] + 1;
        for (int v: g[u]) {
            if (v != p) {
                dfs1(v, u, dist);
            }
        }
    };
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(a, -1, dista);
    dfs1(b, -1, distb);
    int idx = -1;
    int cur = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (dista[i] == distb[i] && dista[i] < cur) {
            idx = i;
            cur = dista[i];
        }
        else if (dista[i] + 1 == distb[i] && distb[i] < cur) {
            cur = distb[i];
            idx = i;
        }
    }
    assert(idx != -1);
    function<void(int,int,vector<int>&,vector<int>&)> dfs2 = [&](int u, int p, vector<int> &cost, vector<int> &depth) {
        cost[u] = 0;
        for (int v: g[u]) {
            if (v != p) {
                dfs2(v, u, cost, depth);
                cost[u] += cost[v] + 2;
                depth[u] = max(depth[u], depth[v] + 1);
            }
        }
    };
    vector<int> cost(n, 0);
    vector<int> depth(n, 0);
    dfs2(idx, -1, cost, depth);
    int ans = cur + cost[idx] - depth[idx];
    cout << ans << '\n';
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
