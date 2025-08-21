#include <bits/stdc++.h>
using namespace std;

int solve_lis(vector<int64_t> const&vec) {
    int n = int(vec.size());

    vector<int64_t> last(n, INT64_MAX);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int64_t v = vec[i];

        // this would just be usual LIS (not non-decreasing)
        // auto it = lower_bound(last.begin(), last.end(), v);
        // *it = v;

        // this ensures non-decreasing
        auto it = upper_bound(last.begin(), last.end(), v);
        *it = v;

        ans = max(ans, int(it - last.begin()) + 1);
    }
    return ans;
}

void solve() {
    int n;
    int64_t v;
    cin >> n >> v;
    auto valid = [&v](int64_t a, int64_t t) {
        return v * t >= abs(a);
    };
    vector<int64_t> t(n), a(n);
    for (auto &ti: t) cin >> ti;
    for (auto &ai: a) cin >> ai;
    vector<pair<int64_t,int64_t>> vals;
    vals.reserve(n);
    for (int i = 0; i < n; i++) {
        int64_t xi = v*t[i]-a[i];
        int64_t yi = v*t[i]+a[i];
        if (valid(a[i], t[i])) {
            vals.emplace_back(xi, yi);
        }
    }
    n = int(vals.size());
    sort(vals.begin(), vals.end());
    vector<int64_t> ys(n);
    for (int i = 0; i < n; i++) {
        ys[i] = vals[i].second;
    }
    int sz = solve_lis(ys);
    cout << sz << '\n';
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
