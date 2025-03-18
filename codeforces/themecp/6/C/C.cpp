#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(n);
    for (auto &x: a) cin >> x;
    for (auto &x: b) cin >> x;
    int mx = 0;
    for (int i = 0; i < n; i++) {
        mx += a[i] / b[i];
    }
    if (mx < k) {
        for (int i = 0; i < n; i++) {
            cout << "0 ";
        }
        cout << '\n';
    }
    else {
        int left = mx;
        int need = k;
        for (int i = 0; i < n; i++) {
            int cur_mx = a[i] / b[i];
            int chosen = max(0, cur_mx - (left - need));
            need -= chosen;
            left -= cur_mx;
            cout << chosen << " ";
        }
        cout << '\n';
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
