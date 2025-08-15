#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    set<int> pref;
    vector<int> suf(n + 1);
    vector<pair<int,int>> vs(n);
    for (auto &[a, b]: vs) cin >> a >> b;
    sort(vs.begin(), vs.end());
    for (int i = n - 1; i >= 0; i--) {
        int b = vs[i].second;
        suf[i] = max(suf[i + 1], b);
    }
    int ans = INT_MAX;
    auto try_diff = [&ans](int mxai, int mxbi) {
        ans = min(ans, abs(mxai - mxbi));
    };
    for (int i = 0; i < n; i++) {
        auto &[ai, bi] = vs[i];
        int suf_mx = suf[i + 1];    // (i, n - 1]

        if (i + 1 < n) {    // force at least one bought gift
            try_diff(ai, suf_mx);
        }
        auto it = pref.lower_bound(ai);
        if (it != pref.end()) {
            int greater_or_equal = *it;
            try_diff(ai, max(suf_mx, greater_or_equal));
        }
        if (it != pref.begin()) {
            int smaller = *prev(it);
            try_diff(ai, max(suf_mx, smaller));
        }
        pref.insert(bi);
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
