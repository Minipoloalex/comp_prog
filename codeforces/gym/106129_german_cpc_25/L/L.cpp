#include <bits/stdc++.h>
using namespace std;

void solve() {
    int t;
    cin >> t;
    int ans = 0;
    for (int i = 0; i <= 1440; i++) {
        int tm_worked = t - i;
        if (tm_worked > 600) {
            continue;
        }
        else if (tm_worked > 540) {
            if (i >= 45) {
                ans = i;
                break;
            }
        }
        else if (tm_worked > 360) {
            if (i >= 30) {
                ans = i;
                break;
            }
        }
        else {
            ans = i;
            break;
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
