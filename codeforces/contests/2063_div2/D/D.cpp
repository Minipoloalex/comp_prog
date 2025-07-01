#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (auto &ai: a) cin >> ai;
    for (auto &bi: b) cin >> bi;
    if (n > m) {
        swap(a, b);
        swap(n, m);
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    vector<int64_t> sma(n / 2 + 1, 0), smb(m / 2 + 1);
    for (int i = 0; i < n / 2; i++) {
        sma[i] = a[n - 1 - i] - a[i];
        if (i > 0) sma[i] += sma[i - 1];
    }
    for (int i = 0; i < m / 2; i++) {
        smb[i] = b[m - 1 - i] - b[i];
        if (i > 0) smb[i] += smb[i - 1];
    }

    int kmax = min(n, min(m, (n + m) / 3));
    cout << kmax << '\n';
    auto value = [&](int k, int select_n) -> int64_t {
        int select_m = k - select_n;
        int64_t ans = 0;
        if (select_n - 1 >= 0) ans += sma[select_n - 1];
        if (select_m - 1 >= 0) ans += smb[select_m - 1];
        return ans;
    };
    for (int k = 1; k <= kmax; k++) {
        int lo = max(0, 2 * k - m), hi = min(k, n - k);
        while (lo < hi) {
            int med = lo + (hi - lo) / 2;
            if (value(k, med) > value(k, med + 1)) { // equal only happens if it doesn't matter if it's the solution
                hi = med;
            }
            else {
                lo = med + 1;
            }
        }
        cout << value(k, lo) << " ";
    }
    cout << '\n';
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
