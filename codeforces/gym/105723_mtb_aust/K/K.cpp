#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, q;
    cin >> n >> q;
    n *= 2;
    vector<int> a(n + 1), mp(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> a[i];
    vector<int> pref(n + 1, 0);
    for (int i = 1; i <= n; ) {
        if (a[i] < 0) {
            i++;
            continue;
        }
        int prev = i;
        while (i <= n && a[i] > 0) {
            mp[i] = prev;
            i++;
        }
        pref[prev]++;
    }
    for (int i = 1; i <= n; i++) {
        pref[i] += pref[i - 1];
    }
    while (q--) {
        int l, r;
        cin >> l >> r;
        l = mp[l];
        cout << pref[r] - pref[l - 1] << '\n';
    }
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
