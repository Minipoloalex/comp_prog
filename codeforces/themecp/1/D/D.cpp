#include <bits/stdc++.h>
using namespace std;

void solve() {
    int64_t a, b, c, d;
    cin >> a >> b >> c >> d;
    pair<int64_t, int64_t> ans = {-1, -1};
    for (int64_t x = a + 1; x <= c; x++) {
        int64_t lcm = x * a * b / gcd(x, a * b);
        int64_t y_test = lcm / x;
        if (y_test <= b) {
            // find closest valid <= d
            y_test = d / y_test * y_test;
        }
        if (y_test > b && y_test <= d) {
            ans = {x, y_test};
        }
    }
    cout << ans.first << " " << ans.second << '\n';
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
