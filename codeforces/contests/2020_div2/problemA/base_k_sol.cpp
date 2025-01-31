#include <bits/stdc++.h>
using namespace std;

// Solution idea presented in the editorial
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        int ans;
        if (k == 1) ans = n;
        else {
            ans = 0;
            while (n > 0) {
                ans += n % k;
                n /= k;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
