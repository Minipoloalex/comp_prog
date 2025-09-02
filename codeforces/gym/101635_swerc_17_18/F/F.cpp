#include <bits/stdc++.h>
using namespace std;

void solve() {
    int64_t w, n;
    cin >> w >> n;
    int64_t area = 0;
    for (int i = 0; i < n; i++) {
        int64_t wi, li;
        cin >> wi >> li;
        area += wi * li;
    }
    int64_t ans = -1;
    for (int64_t l = 1; l <= int64_t(1e4); l++) {
        int64_t test_area = w * l;
        if (test_area == area) {
            ans = l;
            break;
        }
    }
    assert(ans != -1);
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
