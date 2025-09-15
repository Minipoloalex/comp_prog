#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<pair<int,int>> segs(n), segsums(n);
    int64_t ans = 0;
    for (auto &[l, r]: segs) {
        cin >> l >> r;
        ans += r - l;
    }
    for (int i = 0; i < n; i++) segsums[i] = {segs[i].second + segs[i].first, i};
    sort(segsums.begin(), segsums.end());

    for (int i = 0; i < n; i++) ans += segs[i].second;  // sum of all r's
    for (int i = 0; i < (n + 1) / 2; i++) {
        ans -= segsums[i].first;    // sub smallest n / 2 (l + r) values
    }
    if (n % 2 == 1) {
        int64_t val = ans;
        ans = 0;
        for (int i = 0; i < (n + 1) / 2; i++) { // test for values included in the (l + r) subtraction
            int id = segsums[i].second;
            int l = segs[id].first;
            ans = max(ans, val + l);
        }
        val += segsums[n / 2].first;
        for (int i = (n + 1) / 2; i < n; i++) { // test for values not included in the (l + r) subtraction
            int id = segsums[i].second;
            int r = segs[id].second;
            ans = max(ans, val - r);
        }
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
