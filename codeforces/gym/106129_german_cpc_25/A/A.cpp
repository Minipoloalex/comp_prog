#include <bits/stdc++.h>
using namespace std;

void solve() {
    int64_t l, r; cin >> l >> r;

    if (l < r) {
        cout << (l + r) * 2 << '\n';
    } else if (l == r) {
        cout << l * 3 << '\n';
    } else {
        if (l - r >= 3) {
            cout << (l + r) * 2 << '\n';
        } else {
            int64_t x = l - 3;
            int64_t res = (l + x) * 2;

            while (x < r) {
                res -= x;
                x++;
            }
            cout << res << '\n';
        }
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
