#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        int g = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            g = gcd(g, a[i]);
        }
        for (int i = 0; i < n; i++) a[i] /= g;

        int curr = 0;
        int64_t ans = 0;    // e.g.: 1 * 1e5 * 1e5 = 1e10
        for (int i = 0; i < n; i++) {   // select the number that provides the smallest gcd n times
            int mn_gcd = INT_MAX;
            for (int j = 0; j < n; j++) {
                // selecting the same number twice does not matter
                // because, with gcd(a, b, ...) = A, if we "select"/use a or b again, it is the worst case (i.e., gcd = A)
                int curr_gcd = gcd(curr, a[j]);
                mn_gcd = min(mn_gcd, curr_gcd);
            }
            curr = mn_gcd;
            ans += curr;

            // since GCD converges to 1 fast, this allows the algorithm to run in O(N) - explained in Editorial
            if (curr == 1) {
                ans += n - i - 1;
                break;
            }
        }
        cout << ans * g << '\n';
    }
    return 0;
}
