#include <bits/stdc++.h>
using namespace std;

void solve() {
    int r0, x, d, n;
    cin >> r0 >> x >> d >> n;
    string s;
    cin >> s;
    int ans = 0;
    int cur = r0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            ans++;
            cur = max(0, cur - d);
        }
        else {
            assert(s[i] == '2');
            if (cur < x) {
                ans++;
                cur = max(0, cur - d);
            }
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
