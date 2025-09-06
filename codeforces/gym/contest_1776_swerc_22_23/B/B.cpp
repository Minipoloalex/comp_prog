#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, h;
    cin >> n >> h;
    vector<int> x(n);
    for (auto &xi: x) cin >> xi;
    vector<vector<int64_t>> dp(n, vector<int64_t>(n, -1));
    function<int64_t(int,int)> go = [&](int l, int r) -> int64_t {
        if (l == r) return h;

        int64_t &ans = dp[l][r];
        if (ans != -1) return ans;

        int64_t best = INT64_MAX;
        for (int m = l; m < r; m++) {
            int64_t alone = go(l, m) + go(m + 1, r);
            int levels_with_two = (x[r] - x[l] + 1) / 2;
            int64_t together = alone - max(0, h + 1 - levels_with_two);
            best = min(best, together);
        }
        return ans = best;
    };
    int64_t ans = go(0, n - 1);
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
