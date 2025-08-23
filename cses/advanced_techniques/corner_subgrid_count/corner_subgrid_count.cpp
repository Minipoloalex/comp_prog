#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize ("Ofast","unroll-loops")   // not necessary here, but very slightly improved performance
#pragma GCC target("popcnt")    // mandatory pragma to avoid TLE

bitset<3000> g[3000];

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> g[i];

    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int64_t cnt = (g[i] & g[j]).count();
            ans += cnt * (cnt - 1) / 2;
        }
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
