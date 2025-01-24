#include <bits/stdc++.h>
using namespace std;

/*
Test input
1
7
3 2 2 2 2 5 4
*/

void solve() {
    int n;
    cin >> n;
    vector<int> b(n);
    for (auto &x: b) cin >> x;

    vector<pair<int, int>> pref(n), suf(n);
    pref[0] = make_pair(b[0], 0);
    suf[n - 1] = make_pair(b[n - 1], n - 1);
    for (int i = 1; i < n; i++) {
        auto &[ml, l] = pref[i - 1];
        if (b[i] >= ml - (i - l)) {
            pref[i] = make_pair(b[i], i);
        }
        else pref[i] = pref[i - 1];
    }
    for (int i = n - 2; i >= 0; i--) {
        auto &[mr, r] = suf[i + 1];
        if (b[i] >= mr - (r - i)) {
            suf[i] = make_pair(b[i], i);
        }
        else suf[i] = suf[i + 1];
    }
    int ans = 0;
    for (int i = 1; i < n - 1; i++) {
        auto &[ml, l] = pref[i - 1];
        auto &[mr, r] = suf[i + 1];
        // cout << i << ": " << l << " " << ml << " " << r << " " << mr << " " << ml + mr + b[i] - (r - l) << endl;
        ans = max(ans, ml + mr + b[i] - (r - l));
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
