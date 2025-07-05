#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    // sweep line
    vector<pair<int,int>> pts;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        pts.emplace_back(a, 0);
        pts.emplace_back(b, 1);
    }
    sort(pts.begin(), pts.end());
    int ans = 0, cur = 0;
    for (auto &[pt, is_end]: pts) {
        if (is_end) cur--;
        else cur++;
        ans = max(ans, cur);
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
