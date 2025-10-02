#include <bits/stdc++.h>
using namespace std;

const int LOG = 22;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    vector<int> val(1 << LOG, -1);
    for (int i = 0; i < n; i++) {
        val[a[i]] = a[i];
    }
    for (int i = 0; i < LOG; i++) {
        for (int mask = 0; mask < (1 << LOG); mask++) {
            if (mask & (1 << i)) {
                val[mask] = max(val[mask], val[mask ^ (1 << i)]);
            }
        }
    }
    int full_mask = (1 << LOG) - 1;
    for (int i = 0; i < n; i++) {
        int inv = ~a[i] & full_mask;
        cout << val[inv] << " \n"[i == n - 1];
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
