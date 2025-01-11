#include <bits/stdc++.h>
using namespace std;


vector<vector<pair<int,char>>> g;
vector<int> vis;
int dfs(int u, int c) {
    vis[u] = c;
    int dc = 3 - c;
    int ans = 1;
    for (auto &[v, ch]: g[u]) {
        if (ch == 'S') {
            if (!vis[v]) ans *= dfs(v, c);
            else if (vis[v] != c) return 0;
        }
        else {
            assert(ch == 'D');
            if (!vis[v]) ans *= dfs(v, dc);
            else if (vis[v] != dc) return 0;
        }
    }
    return ans;
}

void solve() {
    int n, m;
    cin >> n >> m;
    g.assign(n, {});
    while (m--) {
        char c;
        int a, b;
        cin >> c >> a >> b;
        a--; b--;
        g[a].emplace_back(b, c);
        g[b].emplace_back(a, c);
    }

    vis.assign(n, 0);
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            int res = dfs(i, 1);
            if (res == 0) {
                cnt = -1;
                break;
            }
            cnt++;
        }
    }
    if (cnt == -1) cout << "0\n";
    else {
        cout << "1" << string(cnt, '0') << '\n';
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    freopen("revegetate.in", "r", stdin);
    freopen("revegetate.out", "w", stdout);
    solve();
    return 0;
}
