#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = 998244353;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> p(n+1);
    for (int i = 0; i < n; i++) {
        p[i+1] = p[i] + (s[i] == '(' ? 1 : -1);
    }
    vector<vector<int64_t>> dp(n+1, vector<int64_t>(2));
    int OPEN = 0;
    int CLOSED = 1;
    dp[0][CLOSED] = 1;
    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        dp[i+1] = dp[i]; // do not take
        if (s[i] == '(') {
            dp[i+1][OPEN] += dp[i][OPEN];   // cur open, take open
            dp[i+1][OPEN] += dp[i][CLOSED]; // cur closed, take open
            // if taken as last, can always finish on it: leave that for later though
        }
        if (s[i] == ')') {
            // take and finish, or take and continue
            dp[i+1][CLOSED] += dp[i][CLOSED] + dp[i][OPEN];
            ans += dp[i][CLOSED] + dp[i][OPEN];
        }

        if (p[i+1] < 2) { // not valid for cur = (
            dp[i+1][OPEN] = 0;
        }
        dp[i+1][OPEN] %= MOD;
        dp[i+1][CLOSED] %= MOD;
    }
    int64_t pow2 = 1;
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            // always doable
            ans += pow2;
        }
        pow2 += pow2;
        if (pow2 >= MOD) pow2 -= MOD;
    }
    ans %= MOD;
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
