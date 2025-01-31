#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int64_t k;
        cin >> k;
        // 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
        // By looking at examples and their divisors:
        // - If and only if i is a perfect square, the light-bulb will be off (odd number of divisors)
        // Need to find the k'th number that is not perfect square (editorial solution)
        int64_t ans;
        int64_t lo = 0, hi = 2e18;
        while (lo <= hi) {
            int64_t m = lo + (hi - lo) / 2;
            int64_t nr_on = m - int64_t(sqrtl(m));
            if (nr_on >= k) {
                hi = m - 1;
                ans = m;
            }
            else {
                lo = m + 1;
            }
        }
        // 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
        // 0, 1, 1, 0, 1, 1, 1, 1, 0, 1
        cout << ans << '\n';
    }
    return 0;
}
