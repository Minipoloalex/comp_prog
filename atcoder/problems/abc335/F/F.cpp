#include <bits/stdc++.h>
using namespace std;

// int64_t on everything like usual would also pass the time limit
const int MOD = 998244353;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    int sqrtn = int(ceil(sqrt(n)));
    for (int i = 1; i <= n; i++) cin >> a[i];
    vector<vector<int>> suf(sqrtn, vector<int>(sqrtn, 0));
    vector<int> dp(n + 2, 0);
    dp[n + 1] = 1;
    for (int i = n; i >= 1; i--) {
        int contrib = 0;
        if (a[i] >= sqrtn) {
            for (int x = i + a[i]; x <= n; x += a[i]) {
                contrib = (contrib + dp[x]) % MOD;
            }
        }
        else {
            contrib = suf[a[i]][i % a[i]];
        }
        dp[i] = (contrib + 1) % MOD;
        for (int j = 1; j < sqrtn; j++) {
            suf[j][i % j] = (suf[j][i % j] + dp[i]) % MOD;
        }
    }
    cout << dp[1] << '\n';
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
