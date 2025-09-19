#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = 998244353;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (auto &ai: a) cin >> ai;
    for (auto &bi: b) cin >> bi;
    vector<vector<int64_t>> dp(n + 1, vector<int64_t>(2, -1));
    function<int64_t(int,int)> go = [&](int i, bool swapped_prv) -> int64_t {
        if (i == n) return 1;

        int64_t &mem = dp[i][swapped_prv];
        if (mem != -1) return mem;

        int aval, bval;
        if (i == 0) {
            aval = bval = 0;
        }
        else {
            if (swapped_prv) {
                aval = b[i - 1];
                bval = a[i - 1];
            }
            else {
                aval = a[i - 1];
                bval = b[i - 1];
            }
        }

        int64_t cur = 0;
        if (a[i] >= aval && b[i] >= bval) {
            cur += go(i + 1, 0);
        }
        if (b[i] >= aval && a[i] >= bval) {
            cur += go(i + 1, 1);
        }
        cur %= MOD;
        return mem = cur;
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
