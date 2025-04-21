#include <bits/stdc++.h>
using namespace std;

const int MAX_AI = int(1e6);

void solve() {
    int n;
    cin >> n;
    vector<int> c(MAX_AI + 1, -1);
    for (int i = 0; i < n; i++) {
        int ai, bi;
        cin >> ai >> bi;
        c[ai] = bi;
    }
    reverse(c.begin(), c.end());
    vector<int> lnis(n, INT_MAX);
    int ans = 0;
    for (int ci: c) {
        if (ci != -1) {
            auto it = upper_bound(lnis.begin(), lnis.end(), ci);
            *it = ci;
            ans = max(ans, int(it - lnis.begin() + 1));
        }
    }
    // for (int v: lnis) cout << v << " ";
    // cout << endl;
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
