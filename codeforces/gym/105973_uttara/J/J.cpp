#include <bits/stdc++.h>
using namespace std;

const int64_t BIG = int64_t(1e9);
#define int int64_t

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    int64_t ans = 0;
    int64_t sm = 0;
    int cur_mn1 = 0;
    int prev = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == -1) {
            cur_mn1++;
        }
        else {
            if (a[i] >= prev) {
                sm += a[i];
            }
            else {
                sm = a[i];
            }
            prev = a[i];
        }

        ans = max(ans, sm); // added (shouldn't make a difference)
        if (cur_mn1 > 0 && (i + 1 == n || a[i + 1] != -1)) {
            assert(a[i] == -1);
            ans = max(ans, sm + BIG * cur_mn1);
            if (i + 1 < n && a[i + 1] < prev) {
                sm = cur_mn1 * a[i + 1];
                prev = a[i + 1];
            }
            else if (i + 1 < n) {
                sm += cur_mn1 * a[i + 1];
            }
            cur_mn1 = 0;
        }
        ans = max(ans, sm);
    }
    cout << ans << '\n';
}

signed main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
