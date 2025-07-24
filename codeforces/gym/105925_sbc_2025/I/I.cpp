#include <bits/stdc++.h>
using namespace std;

int64_t get_mx(const array<int64_t,3> &mxs, int id) {
    if (mxs[1] != id) {
        return mxs[0];
    }
    return mxs[2];
}
void add_mx(array<int64_t,3> &mxs, int64_t val, int id) {
    if (val >= mxs[0]) {
        mxs[2] = mxs[0];
        mxs[0] = val;
        mxs[1] = id;
    }
    else if (val > mxs[2]) {
        mxs[2] = val;
    }
}

void solve() {
    int n, t;
    cin >> n >> t;
    vector<vector<int64_t>> cost(n, vector<int64_t>(t));
    for (auto &c: cost) {
        for (auto &cc: c) cin >> cc;
    }
    int l, u;
    cin >> l >> u;
    const int64_t inf = int64_t(1e18);
    vector<vector<int64_t>> dp(t + 1, vector<int64_t>(n, -inf));
    for (int i = 0; i < n; i++) {
        dp[t][i] = 0;
    }
    vector<array<int64_t,3>> mxs(t + 1, {-inf, -1, -inf});
    mxs[t] = {0, -1, 0};
    for (int i = t - 1; i >= 0; i--) {
        for (int s = n - 1; s >= 0; s--) {
            int64_t pref = 0;
            for (int j = 1; j <= u && j + i <= t; j++) {
                pref += cost[s][j + i - 1];
                if (j >= l) {
                    int after = j + i;
                    int64_t mx = get_mx(mxs[after], s);
                    if (mx != -inf) {
                        dp[i][s] = max(dp[i][s], mx + pref);
                    }
                }
            }
            add_mx(mxs[i], dp[i][s], s);
        }
    }
    int64_t ans = -inf;
    for (int s = 0; s < n; s++) {
        ans = max(ans, dp[0][s]);
    }
    if (ans == -inf) {
        ans = -1;
    }
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
