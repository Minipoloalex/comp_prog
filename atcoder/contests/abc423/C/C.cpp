#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, r;
    cin >> n >> r;
    vector<int> l(n);
    for (auto &li: l) cin >> li;
    int mn = INT_MAX, mx = INT_MIN;
    for (int i = 0; i < r; i++) {
        if (l[i] == 0) {
            mn = i;
            break;
        }
    }
    for (int i = n - 1; i >= r; i--) {
        if (l[i] == 0) {
            mx = i;
            break;
        }
    }
    int ans = 0, cnt_locked = 0;
    if (mn != INT_MAX) {
        for (int i = mn + 1; i < r; i++) {
            if (l[i] == 1) cnt_locked++;
        }
        ans += r - mn;
    }
    if (mx != INT_MIN) {
        for (int i = mx - 1; i >= r; i--) {
            if (l[i] == 1) cnt_locked++;
        }
        ans += mx - r + 1;
    }
    ans += cnt_locked;
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
