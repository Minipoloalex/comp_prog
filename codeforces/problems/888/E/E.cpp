#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    auto get_subset_sums = [&](int l, int r, vector<int> &occ) {    // [l, r)
        int len = r - l;
        for (int j = 0; j < (1 << len); j++) {
            int sm = 0;
            for (int i = 0; i < len; i++) {
                if (j & (1 << i)) {
                    sm = (sm + a[l + i]) % m;
                }
            }
            occ.push_back(sm);
        }
    };
    vector<int> occl, occr;
    get_subset_sums(0, n / 2, occl);
    get_subset_sums(n / 2, n, occr);
    sort(occr.rbegin(), occr.rend());
    int ans = 0;
    for (int x: occl) {
        int look_for = m - 1 - x;
        auto it = lower_bound(occr.begin(), occr.end(), look_for, greater<int>());
        if (it != occr.end()) {
            ans = max(ans, x + *it);
        }
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
