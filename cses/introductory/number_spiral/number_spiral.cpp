#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int64_t r, c;
        cin >> r >> c;
        int64_t mx = max(r, c);
        int64_t ans = mx * mx;
        if (mx & 1) {
            ans -= (mx - c) + r - 1;
        }
        else {
            ans -= (mx - r) + c - 1;
        }
        cout << ans << '\n';
    }
    return 0;
}
