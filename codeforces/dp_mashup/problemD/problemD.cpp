#include <bits/stdc++.h>
using namespace std;

int64_t dp[100010][2];

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    vector<int> t(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> t[i];
    vector<int> rsq(n + 1);
    rsq[0] = 0;
    for (int i = 0; i < n; i++) {
        rsq[i + 1] = rsq[i] + a[i];
    }
    const int64_t inf = 1e18;
    for (int i = 0; i < n; i++) {
        dp[i][0] = -inf;
        dp[i][1] = -inf;
    }
    dp[0][0] = 0;
    for (int i = 0; i < n; i++) {
        int passive_nr = (t[i] == 1 ? a[i] : 0);
        dp[i + 1][0] = max(dp[i + 1][0], dp[i][0] + passive_nr);
        if (i + k <= n) {
            dp[i + k][1] = max(dp[i + k][1], dp[i][0] + (rsq[i + k] - rsq[i]));
        }
        dp[i + 1][1] = max(dp[i + 1][1], dp[i][1] + passive_nr);
    }
    cout << dp[n][1] << endl;

    return 0;
}
