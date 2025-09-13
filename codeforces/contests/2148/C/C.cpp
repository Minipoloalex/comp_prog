#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    int ans = 0;
    int lastmin = 0, lastplace = 0;
    for (int i = 0; i < n; i++) {
        int ai, bi;
        cin >> ai >> bi;
        if (bi != lastplace) {
            lastmin++;
            ans++;
        }
        ans += (ai - lastmin) / 2 * 2;
        lastplace = bi;
        lastmin = ai;
    }
    ans += m - lastmin;
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
