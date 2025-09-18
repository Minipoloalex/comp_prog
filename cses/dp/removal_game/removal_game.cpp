#include <bits/stdc++.h>
using namespace std;

void solve_rec(int n, vector<int> const& a) {
    vector<vector<array<int64_t,2>>> dp(n + 1, vector<array<int64_t,2>>(n + 1, {-1,-1}));
    function<int64_t(int,int,bool)> go = [&](int l, int r, bool p) -> int64_t {
        if (l > r) return 0;
        int64_t &mem = dp[l][r][p];
        if (mem != -1) return mem;

        int64_t cur;
        if (p) {
            cur = max(a[l] + go(l + 1, r, !p), a[r] + go(l, r - 1, !p));
        }
        else {
            cur = min(go(l + 1, r, !p), go(l, r - 1, !p));
        }
        return mem = cur;
    };
    int64_t ans = go(0, n - 1, 1);
    cout << ans << '\n';
}

void solve_iterative(int n, vector<int> const& arr) {
    vector<int> a = arr;
    a.insert(a.begin(), 0);
    // just make everything 1-indexed and add space to DP to facilitate implementation
    // note that if we make l [0, n-1] and r [1, n], then we should check l >= r instead of l > r
    // which is very error-prone (messing with two indices with different indexation conventions)
    vector<vector<array<int64_t,2>>> dp(n + 2, vector<array<int64_t,2>>(n + 2, {0, 0}));
    for (int l = n; l >= 1; l--) {
        for (int r = 1; r <= n; r++) {
            if (l > r) continue;
            dp[l][r][0] = min(dp[l+1][r][1],dp[l][r-1][1]);
            dp[l][r][1] = max(a[l]+dp[l+1][r][0],a[r]+dp[l][r-1][0]);
        }
    }
    int64_t ans = dp[1][n][1];
    cout << ans << '\n';
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    solve_iterative(n, a);
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
