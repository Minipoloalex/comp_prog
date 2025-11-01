#include <bits/stdc++.h>
using namespace std;

void solve() {
    int64_t n, s, k;
    cin >> n >> s >> k;

    vector<int64_t> a(n);
    for (auto& x : a) cin >> x;

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > 0) {
            cnt = 0;
            s -= a[i];
        } else {
            cnt++;
            if (cnt == k) {
                s++;
                cnt = 0;
            }
        }
    }

    cout << s << '\n';
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
