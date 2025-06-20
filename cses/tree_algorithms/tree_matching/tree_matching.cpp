#include <bits/stdc++.h>
using namespace std;

void greedy(int n, vector<vector<int>> &g) {
    int ans = 0;
    vector<int> used(n);
    function<void(int,int)> dfs = [&](int u, int p) {
        for (int v: g[u]) {
            if (v != p) {
                dfs(v, u);
            }
        }
        // combine with parent
        if (!used[u] && p != -1 && !used[p]) {
            used[u] = 1;
            used[p] = 1;
            ans++;
        }
    };
    dfs(0, -1);
    cout << ans << '\n';
}

void _dp(int n, vector<vector<int>> &g) {
    vector<vector<int>> dp(n, vector<int>(2, -1));
    function<int(int,int,int)> go = [&](int u, int p, int used) -> int {
        int &ans = dp[u][used];
        if (ans != -1) return ans;

        int total = 0;
        for (int v: g[u]) {
            if (v == p) continue;
            int cur = go(v, u, 0);
            total += cur;
        }
        int mx = total;
        if (!used) {
            for (int v: g[u]) {
                if (v == p) continue;
                int cur = total - go(v, u, 0) + 1 + go(v, u, 1);    // consider taking this pair of nodes
                mx = max(mx, cur);
            }
        }
        return ans = mx;
    };
    int ans = go(0, -1, 0);
    cout << ans << '\n';
}

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    // greedy(n, g);
    _dp(n, g);
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
