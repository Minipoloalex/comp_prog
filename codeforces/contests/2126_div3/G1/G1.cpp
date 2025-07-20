#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    int ans = 0;
    for (int med = 1; med <= 100; med++) {
        vector<int> b(n);
        for (int i = 0; i < n; i++) {
            if (a[i] < med) {
                b[i] = -1;
            }
            else b[i] = 1;
        }
        vector<int> pref(n + 1), prefmn(n + 1, INT_MAX), sufmx(n + 1, INT_MIN);
        for (int i = 0; i < n; i++) {
            pref[i + 1] = pref[i] + b[i];
        }
        prefmn[0] = pref[0];    // 0
        for (int i = 1; i <= n; i++) {
            prefmn[i] = min(prefmn[i - 1], pref[i]);
        }
        sufmx[n] = pref[n];
        for (int i = n - 1; i >= 0; i--) {
            sufmx[i] = max(sufmx[i + 1], pref[i + 1]);
        }

        // for every value a[i]: we check if it can be contained within an array with median X
        // (actually, a median of >= X, but that doesn't matter)
        // if so, then it can be considered the minimum
        // (even if it's "large", e.g. larger than X: we use all possible a[i], so our minimum is minimized)
        for (int i = 0; i < n; i++) {
            // pref[i]:   [0, i-1]
            // prefmn[i]: [0, i-1]
            // sufmx[i]:  [i, n-1]
            if (prefmn[i] <= pref[i + 1] || sufmx[i+1] >= pref[i]) {
                int cur = med - a[i];
                ans = max(cur, ans);
            }
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
