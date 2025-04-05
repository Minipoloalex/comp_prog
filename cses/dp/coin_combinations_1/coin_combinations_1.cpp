#include <bits/stdc++.h>
using namespace std;

const int MOD = int(1e9) + 7;

void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> c(n);
    for (auto &ci: c) cin >> ci;

    // top-down solution
    // vector<int64_t> dp(x + 1, -1);
    // function<int64_t(int64_t)> go = [&](int64_t cur) -> int64_t {
    //     if (cur == x) return 1;

    //     int64_t &ans = dp[cur];
    //     if (ans != -1) return ans;

    //     int64_t v = 0;
    //     for (int i = 0; i < n; i++) {
    //         if (cur + c[i] <= x) {
    //             (v += go(cur + c[i])) %= MOD;
    //         }
    //     }
    //     ans = v;
    //     return ans;
    // };
    // int64_t ans = go(0);

    // bottom-up solution
    vector<int64_t> dp(x + 1, 0);
    dp[0] = 1;
    for (int cur = 0; cur < x; cur++) {
        for (int ci: c) {
            if (cur + ci <= x) {
                (dp[cur + ci] += dp[cur]) %= MOD;
            }
        }
    }
    int64_t ans = dp[x];

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
