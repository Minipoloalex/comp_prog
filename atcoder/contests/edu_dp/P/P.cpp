#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = int(1e9) + 7;

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
    vector<vector<int64_t>> dp(n, vector<int64_t>(2, -1));
    function<int64_t(int,int,int)> go = [&](int u, int p, int can) -> int64_t {
        int64_t &ans = dp[u][can];
        if (ans != -1) return ans;

        int64_t mult = 1;
        for (int v: g[u]) {
            if (v != p) {
                mult *= go(v, u, 1);    // u: white (v can be black)
                mult %= MOD;
            }
        }
        if (can) {
            int64_t multb = 1;
            for (int v: g[u]) {
                if (v != p) {    
                    multb *= go(v, u, 0);   // u: black (v cannot be black)
                    multb %= MOD;
                }
            }
            (mult += multb) %= MOD;
        }
        return ans = mult;
    };
    int64_t ans = go(0, -1, 1);
    cout << ans << '\n';
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
