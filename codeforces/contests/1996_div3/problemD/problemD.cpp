#include <bits/stdc++.h>
using namespace std;

// for (int a = 1; a <= n; a++) {
//     for (int b = 1; a * b <= n && a + b <= x; b++) {
//         ans += std::min((n - a * b) / (a + b), x - a - b);
//     }
// }


int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, x;
        cin >> n >> x;

        // a <= b <= c
        int64_t ans = 0;
        for (int a = 1; a <= x - 2 && a <= ceil(sqrt(n / 3)); a++) {
            for (int b = a; b <= x - a - 1 && b <= ceil(sqrt(n)); b++) {
                // fixing a and b, what are the possible values for c?
                int c = min(x - b - a, (n - a * b) / (a + b));  // max c value
                if (c < b) continue;

                // possible c values [b, c], of length c - b + 1

                // a <= b <= c
                if (a == b && b == c) {
                    ans++;
                }
                else if (a == b) {  // b != c
                    ans++;  // when a == b == c
                    ans += 3 * (c - b); // when a == b && b != c
                }
                else {  // a != b && b != c
                    ans += 3;   // when b == c
                    ans += 6 * (c - b);
                }
            }
        }
        cout << ans << '\n';
    }    
    return 0;
}
