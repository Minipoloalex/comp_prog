#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    int64_t k;
    cin >> n >> k;
    vector<int64_t> a(n);
    sort(a.begin(), a.end());
    for (auto &ai: a) cin >> ai;
    if (k % 2 == 1) {
        for (int i = 0; i < n; i++) {
            if (a[i] % 2 == 1) {
                a[i] += k;
            }
        }
    }
    else {
        int odd;
        for (odd = 3; ; odd += 2) {
            if (gcd(odd, k) == 1) {
                break;
            }
        }
        for (int i = 0; i < n; i++) {
            while (a[i] % odd != 0) {
                a[i] += k;
            }
        }
    }
    for (int64_t v: a) cout << v << " ";
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
