#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k, l;
    cin >> n >> k >> l; k*=2; l*=2;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai, ai*=2;
    int ans = INT_MAX;
    int tm = 0;
    int cur = 0;
    for (int i = 0; i < n && cur < l; i++) {
        int minloc = a[i]-tm;
        int maxloc = a[i]+tm;
        if (i == 0) {
            tm += a[i];
            cur = k;
        }
        else {
            int dist = minloc - cur;
            if (dist <= 0) {
                // use this one instantaneously
                int bestloc = min(maxloc, cur);
                cur = bestloc + k;
            }
            else {
                tm += dist / 2;
                cur += dist / 2;
                cur += k;
            }
        }
        ans = min(ans,tm+max(0,l-cur));
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
