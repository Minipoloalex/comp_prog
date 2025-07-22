#include <bits/stdc++.h>
using namespace std;

int primes[4] = {2, 3, 5, 7};
int64_t cnt_div_by(int64_t mx, int64_t val) {
    return mx / val;
}
int64_t get(int64_t v) {
    int64_t total = 0;
    for (int i = 0; i < (1 << 4); i++) {
        int cnt = 0;
        int64_t nrs = 1;
        for (int j = 0; j < 4; j++) {
            if ((1 << j) & i) {
                nrs *= primes[j];
                cnt++;
            }
        }
        int64_t cur = cnt_div_by(v, nrs);
        if (cnt % 2 == 1) {
            total -= cur;
        }
        else {
            total += cur;
        }
    }
    return total;
}

void solve() {
    int64_t l, r;
    cin >> l >> r;
    int64_t ans = get(r) - get(l - 1);
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
