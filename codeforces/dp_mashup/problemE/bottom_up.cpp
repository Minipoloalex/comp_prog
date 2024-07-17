#include <bits/stdc++.h>
using namespace std;

int64_t dp[1010][2010];

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n, k, p;
    cin >> n >> k >> p;
    vector<int> a(n), b(k);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < k; i++) cin >> b[i];
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    const int64_t inf = int64_t(1e18);

    for (int i = 0; i <= n; i++)
        for (int ki = 0; ki <= k; ki++) dp[i][ki] = inf;

    // bottom up push dp
    dp[0][0] = 0;
    for (int i = 0; i <= n; i++) {  // need this (<= n) because there are transitions (i, k) -> (i + 1, k)
        // do not need (<= k) bcs there are no transitions (i, k) -> (i, k + 1), only (i, k) -> (i + 1, k + 1)
        // drawing an example with the dp table (and arrows) highlights this fact
        for (int ki = 0; ki < k; ki++) {
            // person skips key
            dp[i][ki + 1] = min(dp[i][ki + 1], dp[i][ki]);

            // person selects the key
            if (i < n) {
                int64_t value_using_key = abs(a[i] - b[ki]) + abs(b[ki] - p);
                dp[i + 1][ki + 1] = min(dp[i + 1][ki + 1], max(value_using_key, dp[i][ki]));
            }
        }
    }
    // for (int i = 0; i <= n; i++) {
    //     for (int ki = 0; ki <= k; ki++) cout << dp[i][ki] << " ";
    //     cout << endl;
    // }

    cout << dp[n][k] << '\n';

    return 0;
}
