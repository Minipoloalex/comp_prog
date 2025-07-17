#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    int x;
    cin >> n >> x;
    vector<array<int,3>> c(n);
    for (auto &[l,r,real]: c) cin >> l >> r >> real;
    sort(c.begin(), c.end(), [&](array<int,3> &a, array<int,3> &b) {
        auto &[la, ra, reala] = a;
        auto &[lb, rb, realb] = b;
        return la < lb || (la == lb && reala > realb);
    });
    for (int i = 0; i < n; i++) {
        auto &[l, r, real] = c[i];
        if (l <= x && x <= r) x = max(x, real);
    }
    cout << x << '\n';
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
