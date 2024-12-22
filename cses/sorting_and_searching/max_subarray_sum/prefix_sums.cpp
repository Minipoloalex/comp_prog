#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int64_t> pref(n + 1, 0), mn(n + 1, 0);   // prefix sums and prefix min
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        pref[i] = x + pref[i - 1];
        mn[i] = min(pref[i], mn[i - 1]);
    }
    int64_t ans = LLONG_MIN;
    for (int j = 1; j <= n; j++) {
        ans = max(ans, pref[j] - mn[j - 1]);
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
