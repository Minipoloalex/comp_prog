#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int64_t> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    int64_t ans = 0;
    for (int i = 1; i <= n; i++) {
        if (i % 2 == 1) ans += a[i];
        else ans -= a[i];
    }
    vector<int64_t> pref(n + 1, INT64_MIN);
    for (int i = 1; i <= n; i++) {
        pref[i] = pref[i - 1];
        if (i % 2 == 1) {
            pref[i] = max(pref[i], -2*a[i]-i);
        }
    }
    vector<int64_t> suf(n + 2, INT64_MIN);
    for (int i = n; i >= 1; i--) {
        suf[i] = suf[i + 1];
        if (i % 2 == 1) {
            suf[i] = max(suf[i], -2*a[i]+i);
        }
    }
    int64_t mx = 0;
    for (int i = 2; i <= n; i += 2) {
        int64_t cur = INT64_MIN;
        if (i + 1 <= n) {
            int64_t i_is_lef = 2LL * a[i] - i + suf[i + 1];
            cur = max(cur, i_is_lef);
        }
        if (i - 1 >= 1) {
            int64_t i_is_rig = 2LL * a[i] + i + pref[i - 1];
            cur = max(cur, i_is_rig);
        }
        mx = max(mx, cur);
    }
    mx = max(mx, int64_t(n - 1 - (n % 2 == 0)));  // swapping + with +
    ans += mx;
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
