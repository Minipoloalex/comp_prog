#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int64_t n, m, r, c;
        cin >> n >> m >> r >> c;
        int64_t ans = (n - r) * m + (m - 1) * (n - r) + m - c;
        cout << ans << '\n';
    }
    return 0;
}
