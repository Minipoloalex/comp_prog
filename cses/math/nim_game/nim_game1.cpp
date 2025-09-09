#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    int acc = 0;
    for (int i = 0; i < n; i++) {
        int xi;
        cin >> xi;
        acc ^= xi;
    }
    string ans;
    if (acc == 0) {
        ans = "second";
    }
    else {
        ans = "first";
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
