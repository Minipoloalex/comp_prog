#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> g;
vector<int> dist_to_leaf, max_len;
/*
Another solution:
DFS from random node (e.g. 0) to most distant node
DFS from that distant node to its most distant node -> that distance is the diameter
dfs(u, p, depth)
*/

void dfs(int u, int p) {
    // max_len, dist_to_leaf -> default 0
    for (int v: g[u]) {
        if (v != p) {
            dfs(v, u);
            max_len[u] = max(max_len[u], dist_to_leaf[u] + dist_to_leaf[v] + 1);
            dist_to_leaf[u] = max(dist_to_leaf[u], dist_to_leaf[v] + 1);
        }
    }
}

void solve() {
    int n;
    cin >> n;
    g.assign(n, {});
    max_len.assign(n, 0);
    dist_to_leaf.assign(n, 0);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(0, -1);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, max_len[i]);
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
