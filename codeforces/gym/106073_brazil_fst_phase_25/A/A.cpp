#include <bits/stdc++.h>
using namespace std;

void solve() {
    int64_t n, m;
    cin >> n >> m;
    vector<vector<int64_t>> a(m, vector<int64_t>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[j][i];
        }
    }

    int64_t ans = 0;
    for (auto& row : a) ans += *max_element(row.begin(), row.end());

    cout << ans << endl;
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
