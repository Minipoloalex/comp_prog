#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    vector<int64_t> a(n), b(m);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;

    map<int64_t, int64_t> f;
    int64_t mx = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int64_t diff = b[j] - a[i];
            if (diff >= 0) {
                f[diff]++;
                mx = max(mx, f[diff]);
            }
        }
    }

    for (auto& [v, fr] : f) {
        if (fr == mx) {
            cout << v << endl;
            return;
        }
    }
    cout << "0\n";
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
