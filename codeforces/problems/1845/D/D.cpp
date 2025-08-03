#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int64_t> a(n);
    for (auto &ai: a) cin >> ai;

    int64_t p = 0;
    vector<pair<int64_t,int>> prefs;
    prefs.emplace_back(0, 0);
    for (int i = 0; i < n; i++) {
        p += a[i];
        if (p > 0) {
            prefs.emplace_back(p, i);
        }
    }
    sort(prefs.begin(), prefs.end());
    for (int i = int(prefs.size() - 2); i >= 0; i--) {
        auto &[_, ind] = prefs[i];
        ind = min(ind, prefs[i + 1].second);
    }

    auto possible = [&](int64_t x) -> pair<bool,int64_t> {
        // is it possible to get a value of >= x
        if (lower_bound(prefs.begin(), prefs.end(), pair<int64_t,int>{x, 0}) != prefs.end()) {
            return {true, x};
        }
        for (int i = n - 1; i >= 0; i--) {
            x -= a[i];
            auto it = lower_bound(prefs.begin(), prefs.end(), pair<int64_t,int>{x, 0});
            if (it != prefs.end() && it->second < i) {
                return {true, x};
            }
        }
        return {false, -1};
    };
    const int64_t MAX = int64_t(3e14);
    int64_t lo = 0, hi = int64_t(MAX);
    while (lo < hi) {
        int64_t med = lo + (hi - lo + 1) / 2;
        auto [can, _] = possible(med);
        if (can) {
            lo = med;
        }
        else {
            hi = med - 1;
        }
    }
    auto [_, k] = possible(lo);
    cout << k << '\n';
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
