#include <bits/stdc++.h>
using namespace std;


int main() {
    int t;
    cin >> t;
    while (t--) {
        int64_t n, k;
        cin >> n >> k;
        vector<pair<int64_t, bool>> a(n);
        for (int i = 0; i < n; i++) {
            int64_t ai;
            cin >> ai;
            a[i] = make_pair(ai, 0);
        }
        for (int i = 0; i < n; i++) {
            bool bi;
            cin >> bi;
            a[i].second = bi;
        }
        sort(a.begin(), a.end());

        auto median = [&](int64_t idx) -> int64_t {
            int64_t median_idx = (n - 1) / 2;
            if (n % 2 == 0) {
                if (idx <= median_idx) median_idx++; // [IDX, X1, X2,_] // [_, IDX=X1, X2,_]
                // else [_, X1, _, IDX]
            }
            else {
                if (idx >= median_idx) median_idx--; // [X2, X1, IDX]   // [X2, IDX=X1, _]
                // else [IDX, X1, _]
            }
            return a[median_idx].first;
        };
        auto possible_median = [&](int64_t med_value) -> int64_t {
            // assumes (n - 1) has bi = 0 (else incrementing the max is better)
            int64_t mx_value = a[n - 1].first;
            int64_t k_copy = k;
            int count_possible = 0;

            for (int64_t i = n - 2; i >= 0; i--) {
                auto [ai, bi] = a[i];
                if (med_value - ai > k_copy) break;
                if (ai >= med_value) count_possible++;
                else if (bi) {
                    k_copy -= med_value - ai;
                    count_possible++;
                }
            }
            int64_t required_cnt = (n + 1) / 2;
            if (count_possible < required_cnt) return INT64_MIN;   // not possible to obtain median med_value

            return med_value + mx_value;    // count_possible >= required_cnt
        };

        int64_t mx = 0, mx_idx = -1;
        for (int i = 0; i < n; i++) {
            auto [ai, bi] = a[i];
            if (bi && ai > mx) {    // add to maximum (only those with bi = 1)
                mx = ai;
                mx_idx = i;
            }
        }

        int64_t ans = 0;
        if (mx_idx != -1) {
            ans = mx + k + median(mx_idx);
        }

        int64_t lo = 1, hi = int64_t(2e9);
        while (lo <= hi) {
            int64_t m = (lo + hi) / 2;
            int64_t value = possible_median(m);

            if (value > 0) {    // median m is possible to achieve
                ans = max(ans, value);
                lo = m + 1;
            }
            else {
                hi = m - 1;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
