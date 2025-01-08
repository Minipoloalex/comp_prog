#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, t;
    cin >> n >> t;
    vector<int> k(n);
    for (auto &x: k) cin >> x;
    auto possible = [&](int64_t tm) -> bool {
        int64_t total = 0;
        for (int i = 0; i < n; i++) {
            total += tm / k[i];
        }
        return total >= t;
    };
    int64_t lo = 1, hi = int64_t(*min_element(k.begin(), k.end())) * t;
    while (lo < hi) {
        int64_t m = lo + (hi - lo) / 2;
        if (possible(m)) {
            hi = m;
        }
        else {
            lo = m + 1;
        }
    }
    cout << lo << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
