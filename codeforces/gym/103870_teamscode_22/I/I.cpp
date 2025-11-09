#include <bits/stdc++.h>
using namespace std;

const int MX = int(1e3);
int g[MX][MX];

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            if (s[j] == '*') {
                g[i][j] = 1;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        int cur = 0;
        for (int j = 0; j < m; j++) {
            if (g[i][j]) {
                cur++;
            }
            else cur = 0;
            g[i][j] = cur;
        }
    }
    vector<int> ans(min(n,m)+1);
    for (int j = 0; j < m; j++) {
        int cur = 0;
        for (int i = 0; i < n; i++) {
            cur = min(cur+1, g[i][j]);
            ans[cur]++;
        }
    }
    for (int i = min(n,m); i >= 0; i--) {
        if (i < min(n,m)) {
            ans[i] += ans[i+1];
        }
    }
    for (int i = 2; i <= min(n,m); i++) {
        cout << ans[i] << '\n';
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}
