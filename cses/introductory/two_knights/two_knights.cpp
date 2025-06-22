#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    for (int64_t i = 1; i <= n; i++) {
        int64_t ans = i*i * (i*i - 1) / 2;  // 1e8 * 1e8
        if (i > 2) ans -= 4 * (i - 1) * (i - 2);
        cout << ans << '\n';
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
