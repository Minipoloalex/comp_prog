#include <bits/stdc++.h>
using namespace std;

void solve() {
    int64_t n, k;
    cin >> n >> k;
    vector<int64_t> a(n);
    for (auto &x: a) cin >> x;
    sort(a.rbegin(), a.rend());
    auto possible = [&](int64_t med) -> bool {
        int64_t total = 0;
        for (int i = 0; i < n / 2 + 1; i++) {   // n is odd
            total += max(med - a[i], int64_t(0));
        }
        return total <= k;
    };
    int64_t lo = a.back(), hi = a.front() + k;
    while (lo < hi) {
        int64_t m = (lo + hi + 1) / 2;
        if (possible(m)) {
            lo = m;
        }
        else {
            hi = m - 1;
        }
    }
    cout << lo << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
