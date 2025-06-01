#include <bits/stdc++.h>
using namespace std;

void solve() {
    int r, x;
    cin >> r >> x;
    bool ans;
    if (x == 1) {
        ans = r >= 1600 && r <= 2999;
    }
    else {
        ans = r >= 1200 && r <= 2399;
    }
    cout << (ans ? "Yes" : "No") << '\n';
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
