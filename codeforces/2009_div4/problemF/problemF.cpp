#include <bits/stdc++.h>
using namespace std;

vector<int64_t> a;
vector<int64_t> pref;
int64_t n, q;

int64_t rsq(int64_t i, int64_t j) { // inclusive
    if (j < i) return 0;
    return pref[j] - pref[i - 1];
}

int64_t complete_sum(int64_t l, int64_t r) {    // 0 or 1 indexed
    if (l > r) return 0;
    return (r - l + 1) * rsq(1, n);
}

int64_t partial_sum(int64_t x, int64_t l, int64_t r) {  // [l, r] 1-indexed
    if (r <= n - (x - 1)) return rsq(l + x - 1, r + x - 1);
    if (l > n - (x - 1)) return rsq(l - (n - (x - 1)), r - (n - (x - 1)));
    return rsq(x + l - 1, n) + rsq(1, r - (n - (x - 1)));
}


int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
    
        cin >> n >> q;
        a.resize(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        pref.resize(n + 1);
        pref[0] = 0;
        for (int i = 1; i <= n; i++) pref[i] = pref[i - 1] + a[i - 1];

        while (q--) {
            int64_t l, r;
            cin >> l >> r;

            int64_t ans = 0;
            int64_t left_ci = (l - 1) / n, right_ci = (r - 1) / n;

            int64_t middle_values = complete_sum(left_ci + 1, right_ci - 1);
            // cout << middle_values << " ";
            ans += middle_values;
            if (right_ci != left_ci) {
                int64_t left_value = partial_sum(left_ci + 1, (l - 1) % n + 1, n);
                int64_t right_value = partial_sum(right_ci + 1, 1, (r - 1) % n + 1);
                // cout << left_value << " " << right_value << endl;
                // cout << left_ci << " " << right_ci << " " << l << " " << r << endl;
                ans += left_value + right_value;
            }
            else {
                int64_t value = partial_sum(left_ci + 1, (l - 1) % n + 1, (r - 1) % n + 1);
                // cout << value << endl;
                ans += value;
            }

            cout << ans << '\n';
        }
    }
    return 0;
}
