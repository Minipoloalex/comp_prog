#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int64_t> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    // Basically, it's very easy to derive the formula and extract components to precalculate
    vector<int64_t> pref(n + 1), iia(n + 1), ia(n + 1);
    for (int i = 1; i <= n; i++) pref[i] = pref[i - 1] + a[i];
    for (int i = 1; i <= n; i++) iia[i] = iia[i - 1] + a[i] * i * i;
    for (int i = 1; i <= n; i++) ia[i] = ia[i - 1] + a[i] * i;

    while (q--) {
        int64_t l, r;
        cin >> l >> r;
        int64_t sm = pref[r] - pref[l - 1];
        int64_t sm_i = ia[r] - ia[l - 1];
        int64_t sm_ii = iia[r] - iia[l - 1];
        int64_t ans = (- l * r - l + r + 1) * sm + (r + l) * sm_i - sm_ii; 
        cout << ans << '\n';
    }
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
