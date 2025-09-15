#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    vector<int64_t> pref(n + 1);
    for (int i = 1; i <= n; i++) {
        pref[i] = pref[i - 1] + a[i];
    }
    vector<int64_t> prefpref(n + 1);
    for (int i = 1; i <= n; i++) {
        prefpref[i] = prefpref[i - 1] + pref[i];
    }
    vector<int64_t> value(n + 1), prefvalue(n + 1);
    for (int i = 1; i <= n; i++) {
        int64_t tosub = prefpref[i - 1];
        value[i] = pref[i] * i - tosub;
        prefvalue[i] = prefvalue[i - 1] + value[i];
        // value[i] = value[i - 1] + i * pref[i];   // another way
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        int64_t inside = prefvalue[r] - prefvalue[l - 1];
        int inside_sz = (r - l + 1);    // nr of subarrays starting at l
        int64_t sub = inside_sz * value[l - 1];
        int outside_sz = l - 1;
        int64_t sub2 = outside_sz * ((prefpref[r] - prefpref[l - 1]) - (pref[l - 1] * inside_sz));
        int64_t ans = inside - sub - sub2;
        cout << ans << '\n';
    }
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
