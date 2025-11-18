#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m, k; cin >> n >> m >> k;
    vector<string> a(n);
    for (auto& x : a) cin >> x;

    vector<vector<int>> pf(m, vector<int>(n + 1));

    for (int i = 0; i < m; i++) {
        auto & p = pf[i];

        for (int j = 1; j <= n; j++) {
            p[j] = p[j-1] + (a[j-1][i] == 'x');
        }
    }

    vector<vector<bool>>vis(n, vector<bool>(m));
    using P = pair<int, int>;
    queue<P> q;
    q.emplace(0, 0);
    vis[0][0] = true;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (y > 0) {
            // go left
            int col = y - 1;
            int obs = pf[col][x + k] - pf[col][x];
            if (obs == 0 && !vis[x][col]) {
                q.emplace(x, col);
                vis[x][col] = 1;
            }
        }
        if (y < m - 1) {
            // go right
            int col = y + 1;
            int obs = pf[col][x + k] - pf[col][x];
            if (obs == 0 && !vis[x][col]) {
                q.emplace(x, col);
                vis[x][col] = 1;
            }
        }
        if (x + k < n) {
            // go down
            int row = x + k;
            int obs = (a[row][y] == 'x');
            if (obs == 0 && !vis[x + 1][y]) {
                q.emplace(x + 1, y);
                vis[x + 1][y] = 1;
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // cout << int(vis[i][j]);
            if (vis[i][j]) {
                ans = i;
                break;
            }
        }
        // cout << endl;
    }

    cout << ans + k << endl;
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
