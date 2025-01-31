#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;
    int64_t bad = 0;
    for (int x = 1; x <= 10; x++) {
        vector<int> b(n);
        for (int i = 0; i < n; i++) {
            if (a[i] <= x) b[i] = -1;
            else b[i] = 1;
        }
        for (int i = 1; i < n; i++) {
            b[i] += b[i - 1];
        }
        map<int, int> cnt;
        int64_t cur = 0;
        for (int i = 0, j = 0; i < n; i++) {
            if (a[i] == x) {
                if (cnt[0] == 0) cnt[0] = 1;
                while (j < i) {
                    // this or make b size (n + 1), or just do not save the last prefix sum (editorial solution)
                    // do not need to save last prefix sum bcs it just needs to get compared to others
                    cnt[b[j++]]++;
                }
            }
            cur += cnt[b[i]];
        }
        bad += cur;
    }

    // Subarrays starting at i = 0: n; i = 1: n - 1; ...
    // n + n - 1 + ... + 1
    int64_t good = 1LL * n * (n + 1) / 2 - bad;
    cout << good << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
