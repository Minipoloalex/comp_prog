#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> g(n);
    for (auto &gi: g) cin >> gi;
    sort(g.rbegin(), g.rend());
    int64_t ans = 0;
    for (int i = 0; i + 1 < n; i += 2) {
        ans += max(g[i], g[i + 1]);        
    }
    if (n % 2 == 1) {
        ans += g.back();
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
