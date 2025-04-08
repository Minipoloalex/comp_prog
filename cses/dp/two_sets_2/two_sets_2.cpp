#include <bits/stdc++.h>
using namespace std;

const int MOD = int(1e9) + 7;

int64_t mod_exp(int a, int b, int m) {
    if (b == 0) return 1;
    if (b & 1) return (a * mod_exp(a, b - 1, m)) % MOD;
    int64_t aux = mod_exp(a, b / 2, m);
    return (aux * aux) % MOD;
}

int64_t mod_inv(int v, int m) {
    return mod_exp(v, m - 2, m);
}

void solve() {
    int n;
    cin >> n;
    int MAX_SUM = (n + 1) * n / 2;

    // don't need to handle negative values, since we could just keep track of the sum of one of the sets
    vector<vector<int>> dp(n, vector<int>(2 * MAX_SUM + 20, INT_MAX));
    function<int(int, int)> go = [&](int i, int s) {
        if (i == n) return s == 0 ? 1 : 0;

        int sidx = s + MAX_SUM;
        if (dp[i][sidx] != INT_MAX) return dp[i][sidx];

        int v1 = go(i + 1, s - (i + 1));
        int v2 = go(i + 1, s + (i + 1));
        (dp[i][sidx] = v1 + v2) %= MOD;
        return dp[i][sidx];
    };

    int ans = int((go(0, 0) * mod_inv(2, MOD)) % MOD);
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
