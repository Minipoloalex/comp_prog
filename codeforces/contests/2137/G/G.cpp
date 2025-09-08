#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> rev(n);
    vector<int> deg(n);
    vector<array<int,2>> losing(n,{0,0});
    while (m--) {
        int u, v;
        cin >> u >> v;
        u--;v--;
        deg[u]++;
        rev[v].push_back(u);
    }
    function<void(int,int)> dfs = [&](int u, int cur) {
        // cur is the guy playing from node u
        // the guy that "decided" to move to node u is the other one
        losing[u][cur] = 1;
        if (cur == 0) {
            for (int v: rev[u]) {
                if (losing[v][1 - cur] == 0) {
                    dfs(v, 1 - cur);
                }
            }
        }
        else {
            assert(cur == 1);
            for (int v: rev[u]) {
                if (losing[v][1-cur] == 0 && --deg[v] == 0) {
                    dfs(v, 1 - cur);
                }
            }
        }
    };
    while (q--) {
        int x, u;
        cin >> x >> u;
        u--;
        if (x == 1) {
            if (!losing[u][0]) dfs(u, 0);
            if (!losing[u][1]) dfs(u, 1);
        }
        else {
            assert(x == 2);
            string ans = losing[u][0] ? "NO" : "YES";
            cout << ans << '\n';
        }
    }
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
