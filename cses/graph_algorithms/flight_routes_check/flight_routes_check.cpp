
#include <bits/stdc++.h>
using namespace std;

vector<int> vis;
int dfs(int u, vector<vector<int>> &g) {
    vis[u] = 1;
    int ans = 1;
    for (int v: g[u]) {
        if (!vis[v]) {
            ans += dfs(v, g);
        }
    }
    return ans;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1, vector<int>()), rev(n + 1, vector<int>());
    while (m--) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        rev[b].push_back(a);
    }

    vis.assign(n + 1, 0);
    if (dfs(1, g) != n) {
        cout << "NO\n";
        for (int i = 1; i <= n; i++) {
            if (!vis[i]) {
                cout << "1 " << i << '\n';
                break;
            }
        }
        return;
    }

    vis.assign(n + 1, 0);
    if (dfs(1, rev) != n) {
        cout << "NO\n";
        for (int i = 1; i <= n; i++) {
            if (!vis[i]) {
                cout << i << " 1" << '\n';
                break;
            }
        }
        return;
    }
    cout << "YES\n";
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
