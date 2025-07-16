#include <bits/stdc++.h>
using namespace std;

int msb(uint64_t nr) {
    for (int i = 62; i >= 0; i--) {
        if ((1LL << i) & nr) {
            return i;
        }
    }
    assert(1 == 0);
    return -1;
}

void solve() {
    uint64_t n, l, r, k;
    cin >> n >> l >> r >> k;
    if (n % 2 == 1) {
        cout << l << '\n';
    }
    else {
        int msb_l = msb(l);
        uint64_t need = (1ULL << (msb_l + 1));
        if (need > r || n == 2) {
            cout << "-1\n";
        }
        else {
            if (k == n - 1 || k == n) { // 2 numbers at the end
                cout << need << '\n';
            }
            else {  // needs 4 numbers at least
                cout << l << '\n';
            }
        }
    }
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
