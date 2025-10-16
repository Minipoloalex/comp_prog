#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(k);
    for (auto &ai: a) cin >> ai;
    for (auto &bi: b) cin >> bi;
    sort(a.begin(), a.end());   // largest first
    sort(b.begin(), b.end());   // prioritize smallest vouchers first
    int64_t ans = 0;
    int r = n - 1;
    for (int i = 0; i < k; i++) {
        for (int j = 0; r >= 0 && j < b[i] - 1; j++) {
            ans += a[r--];
        }
        r--;    // for free
        if (r < 0) break;
    }
    while (r >= 0) {
        ans += a[r--];
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
