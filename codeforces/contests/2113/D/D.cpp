#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (auto &ai: a) cin >> ai;
    vector<int> suf(n + 1);
    for (int i = n - 1; i >= 0; i--) {
        suf[i] = max(suf[i + 1], a[i]);
    }
    for (auto &bi: b) cin >> bi;
    vector<int> pref(n + 1, INT_MAX);
    for (int i = 0; i < n; i++) {
        pref[i + 1] = min(pref[i], b[i]);
    }
    auto possible = [&](int x) {
        int mx_outside = suf[x];
        int mn = pref[n + 1 - x];
        int cnt = 0;
        for (int i = 0; i < x; i++) {
            if (a[i] < mn) {
                cnt++;
            }
        }
        if (cnt == 0 || (cnt == 1 && mx_outside > mn)) {
            return true;
        }
        return false;
    };
    int lo = 0, hi = n;
    while (lo < hi) {
        int m = lo + (hi - lo + 1) / 2;
        if (possible(m)) {
            lo = m;
        }
        else {
            hi = m - 1;
        }
    }
    cout << lo << '\n';
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
