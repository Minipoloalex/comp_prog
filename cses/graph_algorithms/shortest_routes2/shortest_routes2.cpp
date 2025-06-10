#include <bits/stdc++.h>
using namespace std;

const int64_t INF = int64_t(1e15);  // could also be 1e18 since at most we will add two INFs together
// floyd warshall
void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int64_t>> d(n, vector<int64_t>(n, INF));
    while (m--) {
        int64_t a, b, c;
        cin >> a >> b >> c;
        a--;b--;
        d[a][b] = min(d[a][b], c);
        d[b][a] = min(d[b][a], c);
    }
    for (int i = 0; i < n; i++) d[i][i] = 0;
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
    while (q--) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        int64_t ans = d[a][b];
        if (ans == INF) {
            ans = -1;
        }
        cout << ans << '\n';
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
