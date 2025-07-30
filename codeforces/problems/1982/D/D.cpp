#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> vs(n, vector<int>(m));
    for (auto &v: vs) {
        for (auto &val: v) cin >> val;
    }
    vector<string> type(n);
    for (auto &s: type) cin >> s;
    int64_t diff = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (type[i][j] == '0') {
                diff -= vs[i][j];
            }
            else {
                diff += vs[i][j];
            }
        }
    }
    int g = 0;
    vector<vector<int>> pref(n + 1, vector<int>(m + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            pref[i + 1][j + 1] = pref[i+1][j] + pref[i][j+1] - pref[i][j] + (type[i][j] == '1' ? 1 : -1);
        }
    }
    for (int i = 0; i + k <= n; i++) {
        for (int j = 0; j + k <= m; j++) {
            int d = pref[i + k][j + k] - pref[i][j + k] - pref[i + k][j] + pref[i][j];
            g = gcd(g, abs(d));       
        }
    }
    bool ans;
    if (g == 0) {
        ans = diff == 0;
    }
    else {
        ans = abs(diff) % g == 0;
    }
    cout << (ans ? "YES" : "NO") << '\n';
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
