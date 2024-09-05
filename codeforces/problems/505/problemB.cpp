#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;

bitset<110> vis;
vector<vector<vi>> el;

void dfs(int u, int c) {
    vis.set(u);
    for (int v: el[c][u]) {
        if (!vis[v]) dfs(v, c);
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    el.assign(m, vvi(n, vi()));
    for (int i = 0; i < m; i++) {
        int ai, bi, ci;
        cin >> ai >> bi >> ci;
        ai--;bi--;ci--;
        el[ci][ai].push_back(bi);
        el[ci][bi].push_back(ai);
    }

    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        u--;v--;

        int ans = 0;
        for (int c = 0; c < m; c++) {
            vis.reset();
            dfs(u, c);
            if (vis[v]) ans++;
        }
        cout << ans << '\n';
    }
    return 0;
}