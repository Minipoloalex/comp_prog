#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;

    sort(a.begin(), a.end());
    vector<int64_t> suf(n+1);
    for (int i = n - 1; i >= 0; i--) {
        suf[i] = suf[i+1] + a[i];
    }
    int64_t cur = 0;
    while (q--) {
        int idx = int(upper_bound(a.begin(), a.end(), cur) - a.begin());
        int cnt = n - idx;
        int64_t sm = max<int64_t>(0, suf[idx] - cur * cnt);
        cout << cnt << " " << sm << '\n';
        int x;
        cin >> x;
        cur += x;
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
