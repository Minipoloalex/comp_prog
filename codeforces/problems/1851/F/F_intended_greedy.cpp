#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<pair<int,int>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i;
    }
    sort(a.begin(), a.end());
    int mask = (1 << k) - 1;
    int best = 0;
    int ansi = 0, ansj = 1;
    int ansx = 0;
    for (int i = 0; i < n - 1; i++) {
        auto [ai, ii] = a[i];
        auto [aj, ij] = a[i + 1];
        int v = ai ^ aj ^ mask;
        if (v > best) {
            best = v;
            ansi = ii;
            ansj = ij;
            ansx = (ai & aj) ^ mask;
        }
    }

    // cout << ((ansx ^ a[ansi]) & (ansx ^ a[ansj])) << " ";
    cout << ansi + 1 << " " << ansj + 1 << " " << ansx << '\n';
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
