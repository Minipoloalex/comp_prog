#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int64_t> x(n), r(n);
    for (auto &xi: x) cin >> xi;
    for (auto &ri: r) cin >> ri;
    map<int,int> mp;
    for (int i = 0; i < n; i++) {
        for (int64_t xv = x[i] - r[i]; xv <= x[i] + r[i]; xv++) {
            int64_t xd = (xv - x[i]) * (xv - x[i]);
            int ymx = (int) sqrt(r[i]*r[i] - xd);
            mp[int(xv)] = max(mp[int(xv)], ymx);
        }
    }
    int64_t ans = 0;
    for (auto &[xv, ymx]: mp) {
        ans += ymx + ymx + 1;
    }
    cout << ans << '\n';
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
