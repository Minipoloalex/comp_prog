#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> t(n);
    for (auto &ti: t) cin >> ti;
    int64_t sm = accumulate(t.begin(), t.end(), 0LL);
    int mx = *max_element(t.begin(), t.end());
    int64_t ans;
    if (mx > sm - mx) {
        ans = mx * 2;
    }
    else {
        ans = sm;
    }
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
