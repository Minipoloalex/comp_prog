#include <bits/stdc++.h>
using namespace std;

int lis(vector<int> &a) {
    vector<int> dp(a.size() + 1, INT_MAX);
    int ans = 0;
    dp[0] = 0;
    for (int ai: a) {
        auto it = lower_bound(dp.begin(), dp.end(), ai);
        dp[it - dp.begin()] = ai;
        ans = max(ans, int(it - dp.begin()));
    }
    return ans;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (auto &x: a) cin >> x;
    for (auto &x: b) cin >> x;
    vector<int> pos(n + 1);
    for (int i = 0; i < n; i++) {
        pos[a[i]] = i + 1;
    }
    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        c[i] = pos[b[i]];
    }
    int ans = lis(c);
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
