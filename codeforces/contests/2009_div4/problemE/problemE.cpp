#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int64_t n, k;
        cin >> n >> k;
        int64_t lo = 0, hi = n - 1;
        int64_t ans = INT64_MAX;
        while (lo <= hi) {
            int64_t m = (lo + hi) / 2;
            // we can do this because the algorithm will avoid cases where lo is too high or hi is too low (for big n and k)

            int64_t a = (k + (k + m)) * (m + 1) / 2, b = (k + m + 1 + k + n - 1) * (n - (m + 1)) / 2;
            // cout << a << " " << b << endl;
            ans = min(ans, abs(a - b));

            if (a == b) break;
            else if (a > b) {
                hi = m - 1;
            }
            else {  // a < b
                lo = m + 1;
            }
        }
        cout << ans << '\n';
    }    
    return 0;
}
