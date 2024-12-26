#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> cities(n), towers(m);
    for (auto &c: cities) cin >> c;
    for (auto &t: towers) cin >> t;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int c = cities[i];
        auto it = upper_bound(towers.begin(), towers.end(), c);
        int curr = INT_MAX;
        if (it != towers.end()) {
            int t = *it;
            curr = min(curr, t - c);
        }
        if (it != towers.begin()) {
            int t = *--it;
            curr = min(curr, c - t);
        }
        ans = max(ans, curr);
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
