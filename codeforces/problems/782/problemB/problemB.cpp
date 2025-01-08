#include <bits/stdc++.h>
using namespace std;

#define EPS 1e-7

void solve() {
    int n;
    cin >> n;
    vector<int> x(n), v(n);
    for (auto &xi: x) cin >> xi;
    for (auto &vi: v) cin >> vi;
    auto possible = [&](double tm) -> bool {
        double lo = 0, hi = int64_t(1e9);
        for (int i = 0; i < n; i++) {
            double ilo = x[i] - v[i] * tm;
            double ihi = x[i] + v[i] * tm;
            lo = max(lo, ilo);
            hi = min(hi, ihi);
        }
        return lo <= hi;
    };
    double lo = 0, hi = 1e9;
    while (lo + EPS < hi) {
        double m = lo + (hi - lo) / 2;
        if (possible(m)) {
            hi = m;
        }
        else {
            lo = m;
        }
    }
    cout << setprecision(16) << lo << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
