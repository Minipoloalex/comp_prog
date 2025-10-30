#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, q;
    cin >> n >> q;
    auto cost = [&](int val) {
        int cnt = 0;
        while (val > 1) {
            val /= 2;
            if (val > 1) val++;
            cnt++;
        }
        return cnt;
    };
    vector<int> a(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int64_t> cnt(n+1), pref(n+1);
    for (int i = 1; i <= n; i++) {
        pref[i] = pref[i-1];
        cnt[i] = cnt[i-1];

        if (a[i] % 2 == 0) {
            int c = cost(a[i]);
            pref[i] += c;
        }
        else {
            int c_if_none = cost(a[i]); // if is: 2^x + 1
            int c_if_one = cost(a[i]+1);
            if (c_if_one != c_if_none) {
                cnt[i]++;
            }
            pref[i] += c_if_none;
        }
    }
    while (q--) {
        int l, r;
        cin >> l >> r;
        int64_t critical_cnt = cnt[r]-cnt[l-1];
        int64_t ans = pref[r] - pref[l-1] + critical_cnt / 2;
        cout << ans << '\n';
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
