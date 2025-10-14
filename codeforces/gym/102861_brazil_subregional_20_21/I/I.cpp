#include <bits/stdc++.h>
#include <cstdint>
using namespace std;

#define sz(v) int((v).size())
constexpr int64_t mod = int64_t(1e9) + 7;

int64_t mod_pow(int64_t b, int64_t e, int64_t m = mod) {
    int64_t res = 1;
    for (; e; e >>= 1) {
        if (e & 1) res = res * b % m;
        b = b * b % m;
    }
    return res;
}

int64_t mod_inv(int64_t n, int64_t m = mod) {
    return mod_pow(n, m - 2);
}

void solve() {
    int n; cin >> n;
    vector<vector<int>> g(n);

    for (int i = 1; i < n; i++) {
        int p; cin >> p;
        g[p-1].push_back(i);
    }

    vector<vector<int64_t>> dp(n, vector<int64_t>(2, -1));
    function<int64_t(int, int)> dfs = [&] (int u, int flag) -> int64_t {
        if (g[u].size() == 0) 
            return dp[u][0] = dp[u][1] = 1;

        if (dp[u][flag] != -1)  
            return dp[u][flag];

        vector<int64_t> pref(sz(g[u]) + 1, 1), suf(sz(g[u]) + 1, 1);
        for (int i = 0; i < sz(g[u]); i++) {
            pref[i + 1] = pref[i] * dfs(g[u][i], 1) % mod;
        }
        for (int i = sz(g[u]) - 1; i >= 0; i--) {
            suf[i] = suf[i + 1] * dfs(g[u][i], 1) % mod;
        }

        int64_t ans = 0;
        for (int i = 0; i < sz(g[u]); i++) {
            ans += pref[i] * suf[i + 1] % mod * dfs(g[u][i], 0) % mod;
        }

        if (flag == 1) {
            ans += pref[sz(g[u])];
        }
        
        return dp[u][flag] = ans % mod;
    };

    cout << dfs(0, 1) << endl;
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
