#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> x(n);
    for (auto &xi: x) cin >> xi;
    // Each position i contains smallest element j that can make sequence of size i
    vector<int> lis(n + 1, INT_MAX);
    lis[0] = 0;
    for (int i = 0; i < n; i++) {
        auto it = lower_bound(lis.begin(), lis.end(), x[i]);
        lis[it - lis.begin()] = x[i];
    }
    int ans = 0;
    for (int i = 0; i <= n && lis[i] != INT_MAX; i++) {
        ans = i;
    }
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
