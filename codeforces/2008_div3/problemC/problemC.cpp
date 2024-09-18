#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int64_t l, r;
        cin >> l >> r;
        int64_t lo = 1, hi = r - l + 1;
        int64_t ans = 0;
        while (lo <= hi) {
            int64_t m = (lo + hi) / 2;
            int64_t last = l + ((m - 1) * m) / 2;
            if (last <= r) {
                ans = m;
                lo = m + 1;
            }
            else {
                assert(last > r);  // not possible
                hi = m - 1;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
