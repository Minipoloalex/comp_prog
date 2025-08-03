#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    // A better implementation would involve reversing the array and handling it the same way twice
    // the only "additional" work would be determining the actual index (not reversed)
    // which is just n - i - 1 if reversed
    // here, by not reversing, I add to duplicate my logic: handle left and handle right
    vector<int> first_occ(n), last_occ(n);
    first_occ[0] = 0;
    for (int i = 1; i < n; i++) {
        if (a[i] == a[i - 1]) {
            first_occ[i] = first_occ[i - 1];
        }
        else first_occ[i] = i;
    }
    last_occ[n - 1] = n - 1;
    for (int i = n - 2; i >= 0; i--) {
        if (a[i] == a[i + 1]) {
            last_occ[i] = last_occ[i + 1];
        }
        else last_occ[i] = i;
    }

    vector<int64_t> pref(n + 1);
    for (int i = 0; i < n; i++) {
        pref[i + 1] = pref[i] + a[i];
    }
    auto rsq = [&](int l, int r) -> int64_t {  // 0-indexed
        return pref[r + 1] - pref[l];
    };
    vector<int> ans(n, INT_MAX);
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            if (a[i - 1] > a[i]) ans[i] = 1;
            else {
                // search on the left
                int first_same = first_occ[i - 1];
                if (first_same > 0) {
                    int first_different = first_same - 1;
                    auto possible = [&](int first_idx) {
                        return rsq(first_idx, i - 1) > a[i];
                    };
                    int lo = 0, hi = first_different;
                    while (lo < hi) {
                        int med = lo + (hi - lo + 1) / 2;
                        if (possible(med)) {
                            lo = med;
                        }
                        else {
                            hi = med - 1;
                        }
                    }
                    if (possible(lo)) {
                        ans[i] = min(ans[i], i - lo);
                    }
                }
            }
        }
        if (i + 1 < n) {
            if (a[i + 1] > a[i]) ans[i] = 1;
            else {
                int last_same = last_occ[i + 1];
                if (last_same < n - 1) {
                    int first_different = last_same + 1;
                    int lo = first_different, hi = n - 1;
                    auto possible = [&](int last_idx) {
                        return rsq(i + 1, last_idx) > a[i];
                    };
                    while (lo < hi) { 
                        int med = lo + (hi - lo) / 2;
                        if (possible(med)) {
                            hi = med;
                        }
                        else {
                            lo = med + 1;
                        }
                    }
                    if (possible(lo)) {
                        ans[i] = min(ans[i], lo - i);
                    }
                }
            }
        }
    }
    for (int v: ans) {
        if (v == INT_MAX) cout << "-1 ";
        else cout << v << " ";
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
