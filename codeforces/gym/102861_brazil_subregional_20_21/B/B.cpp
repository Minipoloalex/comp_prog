#include <bits/stdc++.h>
using namespace std;

int g[11][11];

void solve() {
    int n; cin >> n;
    vector<array<int, 4>> ships(n);
    for (auto& [d, l, r, c] : ships) cin >> d >> l >> r >> c;

    for (auto& [d, l, r, c] : ships) {
        if (d == 0) {
            for (int i = c; i < c + l; i++) {
                if (g[r][i] || c + l > 11) {
                    cout << "N\n";
                    return;
                }
                g[r][i] = 1;
            }
        } else {
            for (int i = r; i < r + l; i++) {
                if (g[i][c] || r + l > 11) {
                    cout << "N\n";
                    return;
                }
                g[i][c] = 1;
            }
        }
    }

    cout << "Y\n";
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
