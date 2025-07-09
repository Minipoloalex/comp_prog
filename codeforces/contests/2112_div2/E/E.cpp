#include <bits/stdc++.h>
using namespace std;

const int MAX_SIZE = int(5e5);
int64_t dp[MAX_SIZE + 1];

void solve() {
    int m;
    cin >> m;
    if (m % 2 == 0) {
        cout << "-1\n";
    }
    else {
        int64_t ans = dp[m];
        cout << ans + 1 << '\n';
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    dp[1] = 0;
    for (int i = 3; i <= MAX_SIZE; i += 2) {
        dp[i] = dp[i - 2] + 1;
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                dp[i] = min(dp[i], dp[i / j] + dp[j]);
            }
        }
    }
    while (t--) {
        solve();
    }
    return 0;
}
