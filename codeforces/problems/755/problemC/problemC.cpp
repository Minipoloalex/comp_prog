#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> g;
vector<int> vis;
void dfs(int u) {
    vis[u] = 1;
    for (int v: g[u]) {
        if (!vis[v]) {
            dfs(v);
        }
    }
}
void solve() {
    int n;
    cin >> n;
    g.assign(n, {});
    vis.assign(n, 0);
    for (int i = 0; i < n; i++) {
        int pi;
        cin >> pi;
        pi--;
        g[pi].push_back(i);
        g[i].push_back(pi);
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(i);
            ans++;
        }
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
