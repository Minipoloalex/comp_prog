#include <bits/stdc++.h>
using namespace std;


void solve() {
    int n, m;
    cin >> n >> m;
    int64_t ans = 0;
    for (int ni = 0; ni < n; ni++) {
        int xi, yi;
        cin >> xi >> yi;
        if (ni == 0) {
            ans = 4 * m;
        }
        else ans += xi * 2 + yi * 2;
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
