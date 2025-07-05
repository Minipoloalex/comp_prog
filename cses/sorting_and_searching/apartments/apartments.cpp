#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n), b(m);
    for (auto &ai: a) cin >> ai;
    for (auto &bi: b) cin >> bi;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int ans = 0;
    for (int i = 0, j = 0; i < n && j < m; i++) {
        int look_for = a[i] - k;
        auto it = lower_bound(b.begin() + j, b.end(), look_for);    // find value >= a[i - k]
        if (it == b.end() || *it > a[i] + k) continue;  // ensure value is <= a[i] + k

        j = int(it - b.begin()) + 1;
        ans++;
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
