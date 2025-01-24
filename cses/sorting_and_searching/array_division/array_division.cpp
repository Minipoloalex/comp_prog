#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> x(n);
    for (auto &a: x) cin >> a;

    auto possible = [&](int64_t m) -> bool {
        int64_t curr = 0, curr_k = 1;
        for (int i = 0; i < n; i++) {
            if (x[i] > m) return false;

            if (curr + x[i] > m) {
                curr_k++;
                curr = 0;
            }
            curr += x[i];
        }
        return curr_k <= k;
    };

    int64_t lo = 0, hi = n * int64_t(1e9) + 10;
    while (lo < hi) {
        int64_t m = (lo + hi) / 2;
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
