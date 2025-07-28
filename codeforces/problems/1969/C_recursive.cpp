#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int64_t> a(n);
    for (auto &ai: a) cin >> ai;
    vector<vector<int64_t>> dp(n, vector<int64_t>(k + 1, -1));
    function<int64_t(int,int)> go = [&](int i, int j) -> int64_t {
        if (i == n) return 0;

        int64_t &ans = dp[i][j];
        if (ans != -1) return ans;

        int64_t best = go(i + 1, j) + a[i];
        int64_t mn = a[i];
        for (int ki = 1; j + ki <= k && i + ki < n; ki++) {
            mn = min(mn, a[i + ki]);
            best = min(best, go(i + 1 + ki, j + ki) + mn * (ki + 1));   // k operations means k + 1 numbers are the same
        }
        return ans = best;
    };
    int64_t ans = go(0, 0);
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
