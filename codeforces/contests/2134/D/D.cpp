#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> dist(n), par(n);
    function<void(int,int,int)> dfs = [&](int u, int p, int d) {
        dist[u] = d;
        par[u] = p;
        for (int v : g[u]) {
            if (v != p) {
                dfs(v, u, d + 1);
            }
        }
    };
    dfs(0, -1, 0);
    int diam_endpoint = int(max_element(dist.begin(), dist.end()) - dist.begin());

    dfs(diam_endpoint, -1, 0);
    int other_ep = int(max_element(dist.begin(), dist.end()) - dist.begin());

    vector<bool> in_diam(n);
    int first_with_3 = -1;
    int cur = other_ep;
    while (cur != diam_endpoint) {
        if (g[cur].size() >= 3 && first_with_3 == -1) {
            first_with_3 = cur;
        }
        in_diam[cur] = true;
        cur = par[cur];
    }
    in_diam[cur] = true;

    if (first_with_3 == -1) {
        cout << "-1\n";
        return;
    }
    int a = par[first_with_3], b = first_with_3, c = -1;
    for (int v: g[first_with_3]) {
        if (in_diam[v]) continue;
        c = v;
        break;
    }
    assert(c != -1);
    cout << a + 1 << " " << b + 1 << " " << c + 1 << '\n';
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
