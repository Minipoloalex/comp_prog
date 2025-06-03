#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (auto &pi: p) cin >> pi;
    sort(p.begin(), p.end());
    int med = p[(p.size() - 1) / 2];
    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        ans += abs(p[i] - med);
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
