#include <bits/stdc++.h>
using namespace std;

const int MAX = int(1e6);

bool good(int i, int sz, int add, int64_t n) {
    int64_t mult = 1;
    int64_t cur = i;
    for (int j = 0; j < sz; j++) {
        if (mult > n / cur) return false;
        mult *= cur;
        cur += add;
    }
    return true;
}

void solve() {
    int64_t n;
    cin >> n;
    int64_t ans = 0;
    int cur_mx_sz = 20;
    for (int i = 1; i < MAX; i++) {
        for (int sz = 3; sz <= cur_mx_sz; sz++) {
            int lo = 0, hi = int(1e9);
            while (lo < hi) {
                int med = lo + (hi - lo + 1) / 2;
                if (good(i, sz, med, n)) {
                    lo = med;
                }
                else {
                    hi = med - 1;
                }
            }
            if (lo == 0) {
                cur_mx_sz = sz - 1;
                break;
            }
            ans += lo;
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
