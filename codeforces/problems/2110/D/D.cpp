#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int64_t> b(n);
    for (auto &bi: b) cin >> bi;
    vector<vector<pair<int,int64_t>>> g(n);
    while (m--) {
        int si, ti, wi;
        cin >> si >> ti >> wi;
        g[si-1].emplace_back(ti-1,wi);
    }
    auto possible = [&](int64_t mx) -> bool {
        vector<int64_t> dp(n + 1, -1);
        dp[0] = 0;
        for (int i = 0; i < n; i++) {
            if (dp[i] != -1) {
                dp[i] = min(mx, dp[i] + b[i]);
            }
            for (auto &[v, w]: g[i]) {
                if (w > dp[i]) continue;  // can't use it
                dp[v] = max(dp[v], dp[i]);
            }
        }
        return dp[n - 1] != -1;
    };
    int64_t lo = 0;
    int64_t hi = accumulate(b.begin(), b.end(), 0LL);
    while (lo < hi) {
        int64_t med = lo + (hi - lo) / 2;
        if (possible(med)) {
            hi = med;
        }
        else {
            lo = med + 1;
        }
    }
    int64_t ans = -1;
    if (possible(lo)) ans = lo;
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
