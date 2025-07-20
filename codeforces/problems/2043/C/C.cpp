#include <bits/stdc++.h>
using namespace std;


void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    int idx = -1;
    for (int i = 0; i < n; i++) {
        if (a[i] != -1 && a[i] != 1) {
            idx = i;
        }
    }
    int mn = 0, mx = 0;
    auto compute_before = [&](int xidx) {
        vector<int> prefmn(n + 1, 0), prefmx(n + 1, 0);

        int min_before = 0;
        int max_before = 0;
        int min_before_close_to_idx = 0;
        int max_before_close_to_idx = 0;
        int pref = 0;
        for (int i = 1; i <= n; i++) {
            pref += a[i - 1];
            prefmn[i] = min(prefmn[i - 1], pref);
            prefmx[i] = max(prefmx[i - 1], pref);
            if (i - 1 < xidx) {
                min_before = min(min_before, pref - prefmx[i - 1]);
                max_before = max(max_before, pref - prefmn[i - 1]);
            }
            if (i - 1 == xidx - 1) {
                min_before_close_to_idx = min(min_before_close_to_idx, pref - prefmx[i - 1]);
                max_before_close_to_idx = max(max_before_close_to_idx, pref - prefmn[i - 1]);
            }
            mn = min(mn, pref - prefmx[i - 1]);
            mx = max(mx, pref - prefmn[i - 1]);
        }
        return array<int,4>{min_before, max_before, min_before_close_to_idx, max_before_close_to_idx};
    };

    // also computes overall min and max (always required regardless of idx)
    auto [min_before, max_before, min_before_close, max_before_close] = compute_before(idx);

    set<int> ans;
    auto insert_values = [&](int mn_val, int mx_val) {
        assert(mn_val <= mx_val);
        for (int i = mn_val; i <= mx_val; i++) {
            ans.insert(i);
        }
    };
    if (idx != -1) {
        int x = a[idx];
        reverse(a.begin(), a.end());
        auto [min_after, max_after, min_after_close, max_after_close] = compute_before(n - idx - 1);
        // reverse(a.begin(), a.end());

        insert_values(min_before, max_before);
        insert_values(min_after, max_after);
        insert_values(min_before_close + min_after_close + x, max_before_close + max_after_close + x);
    }
    else {
        insert_values(mn, mx);
    }
    cout << ans.size() << '\n';
    for (int v: ans) {
        cout << v << " ";
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
