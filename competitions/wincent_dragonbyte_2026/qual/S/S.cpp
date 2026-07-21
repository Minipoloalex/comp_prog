#include <bits/stdc++.h>
using namespace std;

int ten[8];

void solve() {
    int n;
    cin >> n;
    int ans = 0;
    int i = 7;
    while (n) {
        while (n / ten[i] == 0) {
            i--;
        }
        n -= n / ten[i];
        ans++;
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ten[0] = 1;
    for (int i = 1; i < 8; i++) {
        ten[i] = ten[i-1] * 10;
    }
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
