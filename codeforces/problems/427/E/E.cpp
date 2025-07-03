#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int64_t> x(n);
    for (auto &xi: x) cin >> xi;    // already sorted
    vector<int> possible;   // candidate indices from x for our solution
    for (int i = 0; i < n; i++) {
        // this first if is not necessary (but it would work)
        // if (i % m == 0) {
            // avoid same X values (for convexity)
            if (possible.empty() || x[possible.back()] != x[i]) possible.push_back(i);
        // }
    }
    auto value = [&](int pidx) {
        int idx = possible[pidx];
        int64_t y = x[idx];
        int64_t ans = 0;
        for (int i = 0; i < idx; i += m) {
            ans += (y - x[i]) * 2;  // could overflow in int because [-1e9, 1e9]
        }
        for (int i = n - 1; i > idx; i -= m) {
            ans += (x[i] - y) * 2;
        }
        return ans;
    };
    int lo = 0, hi = int(possible.size() - 1);
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
