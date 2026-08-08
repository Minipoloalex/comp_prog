#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = 998244353;
const int MX_M = 3000;

vector<vector<int>> divs(MX_M+1);

void compute_divs() {
    for (int m = 1; m <= MX_M; m++) {
        for (int i = 1; i*i <= m; i++) {
            if (m % i == 0) {
                divs[m].push_back(i);
                if (m / i != i) divs[m].push_back(m / i);
            }
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto &x: a) cin >> x;
    vector<int64_t> dp(m+1);
    vector<int64_t> ndp(m+1);
    bool possible = (a[0] == 0 || a[0] == 1) && (a[1] == 0 || a[1] == 2);
    
    // prove that for 1/x = g/xy + 1/y -> x + g = y
    // also, note that it's not possible to have > 1
    // because we cannot increase the value: x + g <= y
    // since g <= y - x from the definition of gcd
    if (possible) {
        dp[2] = 1;
        for (int i = 2; i < n; i++) {
            ndp.assign(m+1, 0);
            for (int cur = m; cur >= 0; cur--) {
                for (int d: divs[cur]) {
                    int nxt = cur + d;
                    if (nxt <= m && (a[i] == nxt || a[i] == 0)) {
                        (ndp[nxt] += dp[cur]) %= MOD;
                    }
                }
            }
            swap(ndp, dp);
        }
    }
    int64_t ans = accumulate(dp.begin(), dp.end(), 0LL) % MOD;
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    compute_divs();
    while (t--) {
        solve();
    }
    return 0;
}
