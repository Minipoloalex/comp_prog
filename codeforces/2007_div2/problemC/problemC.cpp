#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int64_t n, a, b;
        cin >> n >> a >> b;
        vector<int64_t> c(n);
        int64_t g = gcd(a, b);
        // Editorial solution
        // Bézout's identity: ax + by = gcd
        // Changes in value of each element of the array must be a multiple of gcd
        // (since a and b are multiples of gcd)
        // Also, since ax + by = gcd(a, b), we can perform some operations (x * a, y * b)
        // to increase/decreasse an element just by gcd(a, b)
        for (int i = 0; i < n; i++) {
            cin >> c[i];
            c[i] %= g;
        }
        sort(c.begin(), c.end());
        int64_t ans = c.back() - c.front();
        for (int i = 1; i < n; i++) {
            // consider each i as the minimum
            // the maximum will be the previous minimum + gcd(a, b)
            ans = min(ans, (c[i - 1] + g) - c[i]);
        }
        cout << ans << '\n';
    }
    return 0;
}
