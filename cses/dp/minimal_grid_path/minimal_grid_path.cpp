#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<string> g(n);
    for (auto &s: g) cin >> s;
    auto inside = [&](int r, int c) {
        return r >= 0 && r < n && c >= 0 && c < n;
    };
    string ans(1, g[0][0]);
    g[0][0] = '_';  // using a queue with visited makes more sense, but this works
    for (int i = 0; i < 2 * (n - 1); i++) {
        char bst = 'Z';
        int r = 0, c = i;
        for (int j = 0; j < n; j++, r++, c--) {
            if (!inside(r, c) || g[r][c] != '_') continue;
            if (inside(r + 1, c)) {
                bst = min(bst, g[r + 1][c]);
            }
            if (inside(r, c + 1)) {
                bst = min(bst, g[r][c + 1]);
            }
        }
        r = 0, c = i;
        for (int j = 0; j < n; j++, r++, c--) {
            if (!inside(r, c) || g[r][c] != '_') continue;
            if (inside(r + 1, c) && g[r+1][c] == bst) {
                g[r+1][c] = '_';
            }
            if (inside(r, c + 1) && g[r][c+1] == bst) {
                g[r][c+1] = '_';
            }
        }
        ans += bst;
    }
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
