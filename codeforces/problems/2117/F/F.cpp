#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = int64_t(1e9) + 7;

int64_t powmod(int64_t a, int64_t b, int64_t p) {   // a^b % p
    if (b == 0) return 1;
    if (b % 2 == 1) return (a * powmod(a, b - 1, p)) % p;
    int64_t aux = powmod(a, b / 2, p);
    return (aux * aux) % p;
}

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
    int leafs = 0;
    vector<int> st(n);
    function<void(int,int)> dfs = [&](int u, int p) {
        st[u] = 1;
        int pidx = int(g[u].size() - 1);
        for (int i = 0; i < int(g[u].size()); i++) {
            int v = g[u][i];
            if (v != p) {
                dfs(v, u);
                st[u] += st[v];
            }
            else {
                pidx = i;
            }
        }
        swap(g[u][pidx], g[u].back());
        if (g[u].size() == 1 && u != 0) {
            leafs++;
        }
    };
    dfs(0, -1);
    int64_t ans;
    if (leafs > 2) {
        ans = 0;
    }
    else if (leafs == 1) {
        ans = powmod(2, n, MOD);
    }
    else {
        assert(leafs == 2);
        int node = -1;
        for (int i = 0; i < n; i++) {
            if (g[i].size() == 3 || (g[i].size() == 2 && i == 0)) {
                node = i;
                break;
            }
        }
        assert(node != -1);
        int n1 = g[node][0];
        int n2 = g[node][1];
        int remainder = n - st[n1] - st[n2];
        int mn = min(st[n1], st[n2]);
        int mx = max(st[n1], st[n2]);
        if (mn == mx) {
            ans = powmod(2, remainder + 1, MOD);
        }
        else {
            ans = (powmod(2, n - 2*mn, MOD) + powmod(2, n - (2*mn + 1), MOD)) % MOD;
        }
    }
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
