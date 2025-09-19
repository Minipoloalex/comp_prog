#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) cin >> p[i];
    int c0 = (int)count(p.begin() + 1, p.end(), 0);
    int l = INT_MAX, r = -1;
    vector<int> have(n + 1);
    for (int i = 1; i <= n; i++) {
        if (p[i] == 0) {
            l = min(l, i);
            r = max(r, i);
        }
        else have[p[i]] = 1;
    }
    int mx = n;
    while (mx >= 0 && have[mx]) mx--;
    int mn = 1;
    while (mn <= n && have[mn]) mn++;
    if (c0 == 1) {
        p[l] = mx;
    }

    int ansl = INT_MAX, ansr = INT_MIN;
    for (int i = 1; i <= n; i++) {
        if (p[i] != 0 && p[i] != i) {
            ansr = max(ansr, max(i, p[i]));
            ansl = min(ansl, min(i, p[i]));
        }
    }
    if (l != INT_MAX && r != -1 && c0 > 1) {
        assert(l != r);
        ansr = max(ansr, max(r, mx));
        ansl = min(ansl, min(l, mn));
    }

    int ans = 0;
    if (ansl != INT_MAX && ansr != INT_MIN) {
        ans = ansr - ansl + 1;
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
