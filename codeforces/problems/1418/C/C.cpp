#include <bits/stdc++.h>
using namespace std;


void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;
    vector<vector<int>> dp(n, vector<int>(2, -1));
    function<int(int, int)> go = [&](int i, int f) {
        if (i == n) {
            return 0;
        }

        int &ans = dp[i][f];
        if (ans != -1) return ans;

        int cur = INT_MAX;
        if (i + 1 < n) {
            int cost = (f == 0) ? (a[i] + a[i + 1]) : 0;
            cur = min(cur, cost + go(i + 2, 1 - f));
        }
        int cost = (f == 0) ? a[i] : 0;
        cur = min(cur, cost + go(i + 1, 1 - f));
        return ans = cur;
    };
    int ans = go(0, 0);
    cout << ans << '\n';
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
