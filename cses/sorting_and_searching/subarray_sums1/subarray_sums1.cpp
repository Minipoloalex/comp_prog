#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;

    map<int64_t, int> pref;
    pref[0]++;
    int64_t cur = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        cur += a[i];
        ans += pref[cur - x];
        pref[cur]++;
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
