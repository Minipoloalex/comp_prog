#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    int q;
    cin >> q;
    auto small = [&](string a, string b) {
        int sz = int(a.size());
        for (int i = 0; i + 2 < sz; i++) {
            if (a[i] == '0' && a[i+2] == '0') {
                b[i+1] = '1';
            }
        }
        for (int i = 0; i + 2 < sz; i++) {
            if (b[i] == '1' && b[i+2] == '1') {
                a[i+1] = '1';
            }
        }
        return int(count(a.begin(), a.end(), '1'));
    };

    string se = s;
    string te = t;
    for (int i = 0; i + 2 < n; i++) {
        if (s[i] == '0' && s[i+2] == '0') {
            te[i+1] = '1';
        }
    }
    for (int i = 0; i + 2 < n; i++) {
        if (te[i] == '1' && te[i+2] == '1') {
            se[i+1] = '1';
        }
    }
    vector<int> pref(n+1);
    for (int r = 0; r < n; r++) {
        pref[r+1] = pref[r] + (se[r] == '1');
    }
    vector<int> bad(n);
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--;r--;
        int sz = r - l + 1;
        int ans;
        if (sz <= 3) {
            ans = small(s.substr(l,sz), t.substr(l,sz));
        }
        else {
            ans = pref[r+1] - pref[l];
            if (s[l] != se[l]) ans--;
            if (l != r && s[r] != se[r]) ans--;
            if (s[l+1] != se[l+1] && t[l] == '0') ans--;
            if (s[r-1] != se[r-1] && t[r] == '0') ans--;
        }
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
