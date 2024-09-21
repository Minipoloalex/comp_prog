#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int64_t> a(n);
        int64_t total_sum = 0;
        int64_t mx = 0, mx_idx = -1;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (a[i] > mx) {
                mx = a[i];
                mx_idx = i;
            }
            total_sum += a[i];
        }

        auto unhappy = [&](int64_t x) {
            int cnt = 0;
            double avg = double(total_sum + x) / double(n);
            for (int i = 0; i < n; i++) {
                if (i == mx_idx) continue;
                if (double(a[i]) < avg / 2 - EPS) cnt++;
            }
            return cnt > n / 2;
        };
        int64_t ans = INT64_MAX;

        int64_t lo = 0, hi = int64_t(1e16);
        while (lo <= hi) {
            int64_t m = (lo + hi) / 2;
            if (unhappy(m)) {
                ans = min(ans, m);
                hi = m - 1;
            }
            else {
                lo = m + 1;
            }
        }

        if (ans == INT64_MAX) ans = -1;

        cout << ans << '\n';
    }
    return 0;
}
