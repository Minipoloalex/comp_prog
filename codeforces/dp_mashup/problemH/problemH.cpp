#include <bits/stdc++.h>
using namespace std;

int64_t dp[3010][3];
// dp(i, n)
// min cost for sequence ending at index (must include display at index i), with n displays taken

int main() {
    int n;
    cin >> n;
    vector<int> s(n), c(n);
    for (int i = 0; i < n; i++) cin >> s[i];
    for (int i = 0; i < n; i++) cin >> c[i];

    const int64_t inf = int64_t(1e9);   // almost not enough

    int64_t ans = inf;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            dp[i][j] = inf;
        }
    }

    for (int i = 0; i < n; i++) {
        dp[i][0] = c[i];    // using ith display

        for (int j = 0; j < 2; j++) {
            for (int k = i + 1; k < n; k++) {   // push dp (contributes to others after itself)
                if (s[i] < s[k]) {  // can use k after i ?
                    dp[k][j + 1] = min(dp[k][j + 1], dp[i][j] + c[k]);  // also use display k
                }
            }
        }
        ans = min(ans, dp[i][2]);
    }

    if (ans == inf) ans = -1;
    cout << ans << '\n';
    return 0;
}
