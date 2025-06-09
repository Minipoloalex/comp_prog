#include <bits/stdc++.h>
using namespace std;

const int MOD = int(1e9) + 7;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        g[a-1].push_back(b-1);
    }
    vector<int64_t> dp(n, -1);
    function<int64_t(int)> go = [&](int u) -> int64_t {
        if (u == n - 1) return 1;

        int64_t &ans = dp[u];
        if (ans != -1) return ans;

        int64_t cur = 0;
        for (int v: g[u]) {
            (cur += go(v)) %= MOD;
        }
        return ans = cur;
    };
    cout << go(0) << '\n';
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
