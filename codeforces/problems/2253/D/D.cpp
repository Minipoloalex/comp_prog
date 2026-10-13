#include <bits/stdc++.h>
using namespace std;

void solve() {
    int x, y;
    cin >> x >> y;
    int d = 0;
    int k = 0;
    for (int i = 1; d + i <= x + y; i++) {
        d += i;
        k = i;
    }
    string ans;
    for (int i = k; i >= 1; i--) {
        if (x > y) {
            x -= i;
            ans += 'X';
        }
        else {
            y -= i;
            ans += 'Y';
        }
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
