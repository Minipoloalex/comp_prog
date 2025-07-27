#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    string s;
    cin >> s;
    s.insert(s.begin(), '0');
    vector<int> d(n + 1);
    for (int i = 1; i <= n; i++) {
        if (p[i] != i) {
            int mn = min(i, p[i]);
            int mx = max(i, p[i]);
            d[mn]++;
            d[mx]--;
        }
    }
    for (int i = 1; i <= n; i++) {
        d[i] += d[i - 1];
    }
    set<int> bad;
    for (int i = 1; i <= n; ) {
        while (i <= n && s[i] == 'R') i++;
        while (i <= n && s[i] == 'L') i++;
        if (i <= n) {
            if (d[i - 1] > 0) {
                // contains a segment
                bad.insert(i - 1);
            }
        }
    }
    while (q--) {
        int i;
        cin >> i;
        if (s[i] == 'R' && s[i + 1] == 'R') {
            if (d[i] > 0) {
                bad.insert(i);
            }
        }
        else if (s[i] == 'L' && s[i + 1] == 'R') {
            bad.erase(i);
        }
        if (s[i - 1] == 'L' && s[i] == 'L') {
            if (d[i - 1] > 0) {
                bad.insert(i - 1);
            }
        }
        else if (s[i - 1] == 'L' && s[i] == 'R') {
            bad.erase(i - 1);
        }

        if (s[i] == 'L') s[i] = 'R';
        else s[i] = 'L';

        if (bad.empty()) {
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
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
