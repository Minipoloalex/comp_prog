#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

void solve() {
    int q, k;
    cin >> q >> k;
    vector<int> dp(k + 1, 0);
    dp[0] = 1;
    while (q--) {
        char c;
        int x;
        cin >> c >> x;
        if (c == '+') {
            for (int cur = k; cur >= 0; cur--) {
                if (cur - x >= 0) {
                    (dp[cur] += dp[cur - x]) %= MOD;
                }
            }
        }
        else {
            assert(c == '-');
            for (int cur = 0; cur <= k; cur++) {
                if (cur + x <= k) {
                    (dp[cur + x] += MOD - dp[cur]) %= MOD;
                }
            }
        }
        cout << dp[k] << '\n';
    }
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
