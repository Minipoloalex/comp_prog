#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, t;
    cin >> n >> t;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    auto possible = [&](int m) {
        multiset<int> ms;
        for (int i = 0; i < m; i++) {
            ms.insert(0);
        }
        int mx = 0;
        for (auto &ai: a) {
            int tm = *ms.begin();
            ms.erase(ms.find(tm));
            ms.emplace(tm + ai);
            mx = max(mx, tm + ai);
        }
        return mx <= t;
    };
    int lo = 1, hi = n;
    while (lo < hi) {
        int m = lo + (hi - lo) / 2;
        if (possible(m)) {
            hi = m;
        }
        else {
            lo = m + 1;
        }
    }
    int ans = possible(lo) ? lo : -1;
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
