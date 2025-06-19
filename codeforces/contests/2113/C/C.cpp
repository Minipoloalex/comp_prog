#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<string> g(n);
    vector<vector<int>> pref(n + 1, vector<int>(m + 1, 0));
    for (auto &s: g) {
        cin >> s;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            pref[i + 1][j + 1] = pref[i][j + 1] + pref[i + 1][j] - pref[i][j];
            pref[i + 1][j + 1] += g[i][j] == 'g';
        }
    }
    int total = pref[n][m];
    int mn = INT_MAX;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] == '.') {
                int ri = i + k - 1;
                int rj = j + k - 1;
                int li = i - (k - 1);
                int lj = j - (k - 1);
                ri++;rj++;li++;lj++;
                if (ri > n) ri = n;
                if (rj > m) rj = m;
                if (li < 1) li = 1;
                if (lj < 1) lj = 1;
                int inside = pref[ri][rj] - pref[li - 1][rj] - pref[ri][lj-1] + pref[li - 1][lj - 1];
                mn = min(mn, inside);
            }
        }
    }
    cout << total - mn << '\n';
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
