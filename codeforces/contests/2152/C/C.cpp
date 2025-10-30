#include <bits/stdc++.h>
using namespace std;

array<int,2> operator-(const array<int,2> &a, const array<int,2> &b) {
    return {a[0] - b[0], a[1] - b[1]};
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    vector<array<int,2>> pref(n + 1, array<int,2>{});
    vector<int> lst(n+1,-1);
    for (int i = 0; i < n; i++) {
        pref[i+1] = pref[i];
        pref[i+1][a[i]]++;
        if (i > 0 && a[i-1] == a[i]) {
            lst[i+1] = i;
        }
        else {
            lst[i+1] = lst[i];
        }
    }
    while (q--) {
        int l, r;
        cin >> l >> r;
        array<int,2> cnt = pref[r]-pref[l-1];
        if (cnt[0] % 3 == 0 && cnt[1] % 3 == 0) {
            int add = lst[r] >= l ? 0 : 1;
            int ans = cnt[0] / 3 + cnt[1] / 3 + add;
            cout << ans << '\n';
        }
        else {
            cout << "-1\n";
        }
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
