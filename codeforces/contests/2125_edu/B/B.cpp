#include <bits/stdc++.h>
using namespace std;

void solve() {
    int64_t a, b, k;
    cin >> a >> b >> k;
    if (a > b) swap(a, b);
    int ans;
    int64_t g = gcd(a, b);
    if (b / g <= k) {
        ans = 1;
    }
    else {
        ans = 2;
    }
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
