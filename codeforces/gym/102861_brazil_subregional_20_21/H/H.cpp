#include <bits/stdc++.h>
using namespace std;

uint64_t comb(uint64_t n, uint64_t k) {
    uint64_t r = 1;

    for (uint64_t i = n; i > n - k; i--) {
        r *= i;
        r /= n - i + 1;
    }

    return r;
}

void solve() {
    int n, k;
    cin >> n >> k;

    vector<uint64_t> a(n);
    for (auto& x : a) cin >> x;
    sort(a.begin(), a.end());

    uint64_t l, r;
    cin >> l >> r;

    function<uint64_t(int, int64_t, uint64_t)> f = 
        [&] (int i, int64_t w, uint64_t ch) -> uint64_t 
    {
        if (ch == 0) return w >= 0;
        if (i == -1) return 0;
        if (w < 0) return 0;

        if (a[i] * 2 <= uint64_t(w)) {
            return comb(i + 1, ch);
        }
        
        return f(i-1, w - a[i], ch - 1) + f(i-1, w, ch);
    };

    cout << f(n-1, int64_t(r), k) - f(n-1, int64_t(l-1), k) << endl;
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
