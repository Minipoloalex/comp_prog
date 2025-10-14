#include <bits/stdc++.h>
using namespace std;

int64_t comb(int64_t n, int64_t k) {
    int64_t r = 1;

    for (int64_t i = n; i > n - k; i--) {
        r *= i;
    }
    for (int64_t i = 1; i <= k; i++) {
        r /= i;
    }

    return r;
}

void solve() {
    const int N = 50, K = 25;
    cout << N << ' ' << K << endl;
    const int64_t A = 1, B = int64_t(2e18);
    for (int64_t num = 1, i = 0; i < N; num *= 2, i++) {
        cout << num << ' ';
    }
    cout << endl << A << B << endl;
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
