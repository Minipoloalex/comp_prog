#include <bits/stdc++.h>
using namespace std;

int64_t count_to_zero(int n) {
    return ceil(log(n + 1) / log(3));
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int l, r;
        cin >> l >> r;  // l < r
        int64_t l_to_zero = count_to_zero(l);
        //  l_plus_1_to_zero = l_to_zero + count_to_zero(l + 1);
        int64_t ans = l_to_zero * 2;

        // 2e5 but sum of n over all test cases may be greater
        // need better than O(n) here (could have precomputed prefix sums in O(N) just once)
        int i = l + 1;
        while (i <= r) {    // O(logN)
            int64_t value = count_to_zero(i);
            int64_t next_power_of_3 = (int64_t) pow(3, value);
            int64_t before_next_power_of_3 = min(next_power_of_3 - 1, (int64_t) r);
            ans += (before_next_power_of_3 - i + 1) * value;
            i = next_power_of_3;
        }
        cout << ans << '\n';
    }
    // for (int i = 0; i < 100; i++) {
    //     cout << i << " " << count_to_zero(i) << '\n';
    // }
    return 0;
}
