#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    int64_t ans = 0;
    for (int64_t i = 1; i <= n; i++) {
        ans += i * (n - i + 1);
    }
    vector<int64_t> pref(n + 1, 0);
    for (int i = 0; i < n; i++) {
        pref[i + 1] = pref[i] + (s[i] == '0' ? 1 : -1);
    }
    sort(pref.begin(), pref.end());
    for (int i = 0; i <= n; i++) {
        ans += pref[i] * i;
        ans -= pref[i] * (n + 1 - i - 1);
    }
    cout << ans / 2 << '\n';
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
