#include <bits/stdc++.h>
using namespace std;

void solve() {
    int64_t a, b, x, y;
    cin >> a >> b >> x >> y;
    if (a == b + 1 && (a % 2 == 1)) {
        cout << y << '\n';
    }
    else if (a > b) {
        cout << "-1\n";
    }
    else {
        y = min(x, y);
        int64_t diff = b - a;
        int64_t ans;
        if (a % 2 == 1) {
            ans = diff / 2 * y + (diff + 1) / 2 * x;
        }
        else {
            ans = (diff + 1) / 2 * y + diff / 2 * x;
        }

        cout << ans << '\n';
    }
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
