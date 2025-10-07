#include <bits/stdc++.h>
using namespace std;
const int MAX = int(2e5);
void solve() {
    int n;
    cin >> n;
    vector<int> t(n);
    for (auto &ti: t) cin >> ti;
    auto possible = [&](int ppl) {
        int64_t acc = 0;
        for (int i = 0; i < n; i++) {
            int64_t cur = acc + t[i];
            if (i == n - 1) {
                if (cur > ppl) {
                    return false;
                }
            }
            else {
                if (cur > ppl * 2) {
                    return false;
                }
                else {
                    // take out as much trash as possible
                    int64_t need2 = max<int64_t>(0, cur - ppl);
                    acc = need2 * 2;
                }
            }
        }
        return true;
    };
    int lo = 0, hi = MAX;
    while (lo < hi) {
        int med = lo + (hi - lo) / 2;
        if (possible(med)) {
            hi = med;
        }
        else {
            lo = med + 1;
        }
    }
    cout << lo << '\n';
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
