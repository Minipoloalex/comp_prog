#include <bits/stdc++.h>
using namespace std;


int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int64_t n, k;
        cin >> n >> k;

        int64_t mn = 0, mx = 0;
        vector<int64_t> a(n), b(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            mx = max(mx, a[i]);
        }
        for (int i = 0; i < n; i++) cin >> b[i];

        auto ops = [&](int64_t x) -> int64_t {
            int64_t ans = 0;
            for (int i = 0; i < n; i++) {
                if (a[i] >= x) {
                    ans += (a[i] - x) / b[i] + 1;
                }
            }
            return ans;
        };

        int64_t x = 0, ans_op_count = 0;
        while (mn <= mx) {
            int64_t middle = (mn + mx) / 2;
            int64_t op_count = ops(middle);
            if (op_count >= k) {
                if (middle > x) {
                    x = middle;
                    ans_op_count = op_count;
                }
                mn = middle + 1;
            }
            else {
                mx = middle - 1;
            }
        }
        // cout << x << ' ';

        int64_t ans = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] >= x) {
                int64_t count = (a[i] - x) / b[i] + 1;
                int64_t last_value = a[i] - b[i] * (count - 1);
                ans += ((a[i] + last_value) * count) / 2;
            }
        }
        cout << ans - (ans_op_count - k) * x << '\n';
    }
    return 0;
}
