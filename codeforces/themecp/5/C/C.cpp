#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;
    sort(a.begin(), a.end());

    int ans = INT_MAX;
    for (int i = 0; i < n; i++) {
        auto it = lower_bound(a.begin(), a.end(), a[i] / 2 + 1);
        assert(it != a.end());
        int j = int(it - a.begin());
        if (j > 0) {
            // consider using the one before it
            int v1 = a[j - 1];
            int v2 = a[j];
            int v3 = a[i];
            if (v1 + v2 > v3) j--;
        }
        ans = min(ans, n - i - 1 + j);
        // cout << i << " " << j << " " << n - i - 1 + j << endl;
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
