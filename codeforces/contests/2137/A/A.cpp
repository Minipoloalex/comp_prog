#include <bits/stdc++.h>
using namespace std;

void solve() {
    int64_t k, x;
    cin >> k >> x;
    int64_t ans = x << k;
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
