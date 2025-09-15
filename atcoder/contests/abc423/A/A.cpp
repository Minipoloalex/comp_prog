#include <bits/stdc++.h>
using namespace std;

void solve() {
    int64_t x, c;
    cin >> x >> c;
    int64_t ans = 0;
    for (int64_t i = 0; i <= x; i += 1000) {
        if (i + c * i / 1000 <= x) {
            ans = max(ans, i);
        }
    }
    cout << ans << '\n';
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
