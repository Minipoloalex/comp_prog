#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    vector<int64_t> pref(n + 1);
    for (int i = 1; i <= n; i++) {
        pref[i] = pref[i - 1] + a[i];
    }
    auto can = [&](int d) {
        int x = m - d + 1;
        int i = 1;
        while (i <= n) {
            int first_idx_larger = int(
                lower_bound(pref.begin() + i, pref.end(), pref[i - 1] + x) - pref.begin());
            if (first_idx_larger > n) {
                break;
            }
            int64_t actual_used = pref[first_idx_larger] - pref[i - 1];
            if (actual_used > m) {
                // we would need more than we can have (with no resetting)
                return false;
            }
            i = first_idx_larger + 1;
        }
        return true;
    };
    for (int d = 1; d <= m; d++) {
        if (can(d)) {
            cout << d << '\n';
            return;
        }
    }
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
