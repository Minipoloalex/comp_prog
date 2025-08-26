#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    int64_t ans = 0;
    for (int i = 0; i < n; i += 2) {
        // go through all odds
        int mn = INT_MAX;
        if (i > 0) {
            mn = a[i - 1];
        }
        if (i + 1 < n) {
            mn = min(mn, a[i + 1]);
        }
        int ops = max(0, a[i] - mn);
        a[i] = a[i] - ops;
        ans += ops;
    }
    for (int i = 1; i < n; i += 2) {    // go through evens
        int sm = a[i - 1];
        if (i + 1 < n) {
            sm += a[i + 1];
        }
        if (sm > a[i]) {
            // sub from a[i + 1]
            int ops = sm - a[i];
            a[i + 1] -= ops;    // only happens if i + 1 is actually indexable
            ans += ops;
        }
    }
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
