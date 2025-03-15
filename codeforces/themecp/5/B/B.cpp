#include <bits/stdc++.h>
using namespace std;

void solve() {
    int64_t n, x, y;
    cin >> n >> x >> y;
    int64_t cnt_both = n / lcm(x, y);
    int64_t cntplus = n / x - cnt_both;
    int64_t cntminus = n / y - cnt_both;
    int64_t ans = (n + (n - cntplus + 1)) * cntplus / 2 - (1 + cntminus) * cntminus / 2;
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
