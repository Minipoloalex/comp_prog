#include <bits/stdc++.h>
using namespace std;

void solve() {
    int x;
    cin >> x;   // 1e5 * 1e3 -> may not pass
    int ans = 1, cur = 0;
    for (int i = 2; i * i <= x; i++) {
        cur = 0;
        while (x % i == 0) {
            x /= i;
            cur++;
        }
        ans *= (cur + 1);
    }
    if (x > 1) ans *= 2;
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
