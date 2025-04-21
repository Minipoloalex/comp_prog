#include <bits/stdc++.h>
using namespace std;

void solve() {
    int a, b;
    cin >> a >> b;
    int mx = max(a, b);
    int mn = min(a, b);
    int total = a + b;
    string ans;
    if (total % 3 == 0) {
        if (mn * 2 < mx) ans = "NO";
        else ans = "YES";
    }
    else {
        ans = "NO";
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
