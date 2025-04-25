#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, a, b;
    cin >> n >> a >> b;
    vector<int64_t> pref(n + 1, 0);
    for (int i = 0; i < n; i++) {
        int ai;
        cin >> ai;
        pref[i + 1] = pref[i] + ai;
    }
    
    multiset<int64_t> s = {0};
    int64_t ans = INT64_MIN;
    int l = 0, r = 1;
    int mx_win_size = b - a + 1;
    for (int i = 1; i <= n; i++) {
        int64_t cur = pref[i];

        if (int(s.size()) > mx_win_size) {
            s.erase(s.find(pref[l++]));
        }
        if (i >= a) {
            int64_t mn = *s.begin();
            ans = max(ans, cur - mn);
            // cout << i << " " << cur - mn << endl;
            s.insert(pref[r++]);
        }
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
