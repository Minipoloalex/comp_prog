#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        g[a-1].push_back(b-1);
    }
    vector<int> dp(n, -1), nxt(n, -1);
    function<int(int)> go = [&](int u) {
        if (u == n - 1) return 1;

        int &ans = dp[u];
        if (ans != -1) return ans;

        int mx = INT_MIN;
        for (int v: g[u]) {
            int aux = go(v) + 1;
            if (aux > mx) {
                mx = aux;
                nxt[u] = v;
            }
        }
        return ans = mx;
    };
    int ans = go(0);
    if (ans < 0) {
        cout << "IMPOSSIBLE\n";
    }
    else {
        cout << ans << '\n';
        int cur = 0;
        while (cur != n - 1) {
            cout << cur + 1 << " ";
            cur = nxt[cur];
        }
        cout << cur + 1 << '\n';
    }
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
