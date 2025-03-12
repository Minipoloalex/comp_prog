#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;
    vector<int64_t> pref(n + 1, 0);
    vector<int> mx(n + 1, 0);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        pref[i + 1] = pref[i] + a[i];
        mx[i + 1] = max(mx[i], a[i]);
        if (pref[i + 1] - mx[i + 1] == mx[i + 1]) {
            ans++;
        }
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
