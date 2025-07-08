#include <bits/stdc++.h>
using namespace std;

void solve() {
    int a, x, y;
    cin >> a >> x >> y;
    bool ans;
    int mx = max(x, y);
    int mn = min(x, y);
    if (a > mn && a < mx) {
        ans = false;
    }
    else ans = true;
    cout << (ans ? "YES" : "NO") << '\n';
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
