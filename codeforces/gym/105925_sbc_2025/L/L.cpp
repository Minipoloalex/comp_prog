#include <bits/stdc++.h>
using namespace std;

void solve() {
    int64_t m;
    cin >> m;
    m *= int64_t(8e6);
    int ans = int(ceil(log2(m)));
    cout << ans << '\n';
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
