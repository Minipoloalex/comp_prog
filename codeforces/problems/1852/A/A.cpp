#include <bits/stdc++.h>
using namespace std;

int64_t MAX = int64_t(1e11);

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    auto possible = [&](int64_t x) {    // is it possible to achieve a value of <= x?
        int64_t removed_cnt = 0;
        int64_t xx = x;
        for (int ki = 0; ki < k && xx > 0; ki++) {
            // could have done this with a decreasing pointer instead
            int cnt = int(upper_bound(a.begin(), a.end(), xx) - a.begin());
            removed_cnt += cnt;
            xx -= cnt;
            if (cnt == 0) break;
        }
        return removed_cnt < x;
    };
    int64_t lo = 1, hi = MAX;
    while (lo < hi) {
        int64_t med = lo + (hi - lo) / 2;
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
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
