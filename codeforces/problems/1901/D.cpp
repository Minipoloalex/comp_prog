#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int64_t> a(n);
    for (auto &ai: a) cin >> ai;
    // minimum strength required if chosen from the left of i, and from the right of i
    vector<int64_t> mnleft(n), mnright(n), mx(n);
    for (int i = 0; i < n; i++) {
        int rig = n - i - 1;
        int lef = i;
        mnleft[i] = a[i] + lef;
        mnright[i] = a[i] + rig;
        mx[i] = max(mnleft[i], mnright[i]);
    }
    // build prefix of the right and suffix of the left
    vector<int64_t> pref(n + 1, INT_MIN), suf(n + 1, INT_MIN);
    for (int i = 0; i < n; i++) {
        pref[i + 1] = max(pref[i], mnright[i]);
    }
    for (int i = n - 1; i >= 0; i--) {
        suf[i] = max(suf[i + 1], mnleft[i]);
    }
    int64_t ans = INT64_MAX;
    for (int i = 0; i < n; i++) {
        // pref[i]: does not contain i
        // suf[i]: contains i, suf[i + 1]: does not contain i
        int64_t cur = max(pref[i], suf[i + 1]);
        cur = max(cur, a[i]);
        ans = min(ans, cur);
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
