#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> x(n);
    for (auto &xi: x) cin >> xi;
    int64_t ans = 0;
    set<int> cur;
    int l = 0;
    for (int i = 0; i < n; i++) {
        while (cur.count(x[i])) {
            cur.erase(x[l++]);
        }
        cur.insert(x[i]);
        // add subarrays that end on this position (i)
        // any subarray within [l, i]
        int sz = i - l + 1;
        ans += sz;
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
