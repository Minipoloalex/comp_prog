#include <bits/stdc++.h>
using namespace std;

void solve() {
    int64_t n, a, r, m;
    cin >> n >> a >> r >> m;
    m = min(m, a + r);
    vector<int> h(n);
    for (auto &hi: h) cin >> hi;
    sort(h.begin(), h.end());
    int mx = h.back();
    auto value = [&](int y) {   // we can prove value(y) is convex
        int64_t sm = 0;
        int64_t cnts = 0, cntl = 0;
        for (int i = 0; i < n; i++) {
            if (h[i] < y) {
                cnts += y - h[i];
                sm += (y - h[i]) * a;
            }
            if (h[i] > y) {
                cntl += h[i] - y;
                sm += (h[i] - y) * r;
            }
        }
        sm -= min(cnts, cntl) * (a + r - m);
        return sm;
    };
    int lo = 0, hi = mx;    // the result does not need to be one of the input heights
    while (lo < hi) {
        int med = lo + (hi - lo) / 2;
        if (value(med) < value(med + 1)) {
            hi = med;
        }
        else {
            lo = med + 1;
        }
    }
    cout << value(lo) << '\n';
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
