#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (auto &pi: p) cin >> pi;
    int64_t ans = 0;
    // based on the contribution of each value for all subarrays
    for (int i = 0; i < n; i++) {
        if (i + 1 < n && p[i] < p[i + 1]) {
            // will appear in all of the left ones, but none of the right ones
            ans += i + 1;
        }
        else {
            // will appear in all of the left ones, and also the right ones
            ans += int64_t(i + 1) * (n - i);
        }
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
