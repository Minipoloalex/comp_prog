#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    using T = array<int,3>;
    vector<T> portals(n);
    vector<int> vals;
    for (int i = 0; i < n; i++) {
        int li, ri, ai, bi;
        cin >> li >> ri >> ai >> bi;
        portals[i] = {li, ri, bi};
        vals.push_back(bi);
    }
    sort(portals.begin(), portals.end());
    vector<int> prefmx(n + 1);
    for (int i = 0; i < n; i++) {
        prefmx[i + 1] = max(prefmx[i], portals[i][2]);
    }
    int q;
    cin >> q;
    vector<int> qs(q);
    for (auto &x: qs) {
        cin >> x;
        vals.push_back(x);
    }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    auto get_idx = [&](int v) {
        return int(lower_bound(vals.begin(), vals.end(), v) - vals.begin());
    };
    auto get_mx_b = [&](int value) {
        // could have done this with a LazySegTree instead (definitely overkill)
        auto it = upper_bound(portals.begin(), portals.end(), T{value, INT_MAX, INT_MAX});
        int mx_b = 0;
        if (it != portals.begin()) {
            it--;
            int idx = int(it - portals.begin());
            mx_b = prefmx[idx + 1]; // 1-indexed
        }
        return mx_b;
    };
    int sz = int(vals.size());
    vector<int> dp(sz, 0);
    for (int i = sz - 1; i >= 0; i--) {
        int coord_val = vals[i];
        int mx_b = get_mx_b(coord_val);
        dp[i] = coord_val;
        if (mx_b > coord_val) {
            dp[i] = max(dp[i], dp[get_idx(mx_b)]);
        }
    }
    for (int x: qs) {
        int idx = get_idx(x);
        cout << dp[idx] << " ";
    }
    cout << '\n';
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
