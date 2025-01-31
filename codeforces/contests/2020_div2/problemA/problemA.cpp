#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        // n -> n - k^x, x >= 0
        int ans;
        if (k == 1) {
            ans = n;
        }
        else {
            ans = 0;
            while (n >= k) {
                int x = int(log2(n) / log2(k));
                n -= int(pow(k, x));
                ans++;
            }

            if (n > 0) {
                ans += n;
                // cout << n << " ";
            }
            // cout << endl;
        }
        cout << ans << '\n';
    }
    return 0;
}
