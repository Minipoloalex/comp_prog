#include <bits/stdc++.h>
using namespace std;

int64_t dp[1010];

int main() {
    int n;
    cin >> n;
    vector<int> p(n);

    int64_t mod = int64_t(1e9 + 7);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
    }

    dp[0] = 0;  // getting to 1 costs 0
    for (int i = 0; i < n; i++) {
        // first need to get to i (dp[i]), then traverse through p[i] (1).
        // now need to get to i (dp[i]), but already on p[i], so need to exclude dp[p[i]] from dp[i]
        // finally, go first portal to get to i + 1

        // dp[i + 1] = dp[i] + 1 - dp[p[i]] + dp[i] + 1;
        dp[i + 1] = (dp[i] * 2 - dp[p[i]] + 2 + mod) % mod;
        // cout << dp[i + 1] << " ";
    }
    // cout << '\n';

    cout << dp[n] << '\n';
    return 0;
}
