#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int64_t> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    uint64_t ans = 0;
    auto handle = [&](vector<int64_t> &vec) {
        sort(vec.begin(), vec.end());
        int64_t p = 0;
        for (int i = 0; i < n; i++) {
            ans += 1LL * i * vec[i] - p;
            p += vec[i];
        }
    };
    handle(x);
    handle(y);
    cout << ans << '\n';
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
