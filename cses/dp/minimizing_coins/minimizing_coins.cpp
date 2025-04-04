#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 100;
const int MAX_C = int(1e6);
int dp[MAX_C + 1];

void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> c(n);
    for (auto &xi: c) cin >> xi;

    for (int i = 0; i <= x; i++) dp[i] = INT_MAX;
    dp[0] = 0;
    for (int cur = 0; cur < x; cur++) {
        if (dp[cur] == INT_MAX) continue;
        for (int i = 0; i < n; i++) {
            if (cur + c[i] <= x) {
                dp[cur + c[i]] = min(dp[cur + c[i]], dp[cur] + 1);
            }
        }
    }
    int ans = dp[x];
    if (ans == INT_MAX) ans = -1;
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
