#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;
    int odds = 0, evens = 0;
    int64_t cur = 0;
    vector<int> dp(n + 1, 0);
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 0;
    for (int i = 3; i <= n; i++) {
        dp[i] = dp[i - 3] + 1;
    }
    for (int i = 0; i < n; i++) {
        if (a[i] % 2 == 0) evens++;
        else odds++;
        cur += a[i];
        if (i == 0) {
            cout << cur << " ";
        }
        else {
            cout << cur - dp[odds] << " ";
        }
    }
    cout << '\n';
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
