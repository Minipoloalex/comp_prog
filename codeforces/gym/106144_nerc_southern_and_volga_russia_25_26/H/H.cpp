#include <bits/stdc++.h>
using namespace std;

void solve() {
    int64_t lm, rm, lb, rb;
    cin >> lm >> rm >> lb >> rb;
    auto can = [&](int64_t x) {
        if (x == 0) return true;
        int64_t l = rm-x+1    +lm, r = rm   +lm;
        // cout << l << " " << r << " " << (lb+   lb+x*2-1) << endl;
        return l+r >= (lb+   lb+x*2-1)*2;
    };
    int64_t lo = 0, hi = min((rb-lb+1)/2,rm-lm);
    while (lo < hi) {
        int64_t med = lo + (hi - lo + 1) / 2;
        // cout << med << " " << boolalpha << can(med) << endl;
        if (can(med)) {
            lo = med;
        }
        else {
            hi = med - 1;
        }
    }
    can(96);
    cout << lo << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
