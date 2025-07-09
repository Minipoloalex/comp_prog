#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m)), vis(n, vector<int>(m, 0));
    using T = array<int, 3>;
    vector<T> pq(n * m);

    auto idx = [m](int i, int j) { return i * m + j; };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            pq[idx(i, j)] = {a[i][j], i, j};
        }
    }

    sort(pq.rbegin(), pq.rend());

    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};

    auto go = [&] (int h, int x, int y) {
        queue<T> q;
        q.push({x, y, h});

        while (!q.empty()) {
            auto [i, j, c] = q.front();
            q.pop();

            for (int d = 0; d < 4; d++) {
                int ni = i + dx[d];
                int nj = j + dy[d];

                if (ni < 0 || ni >= n) continue;
                if (nj < 0 || nj >= m) continue;
                if (vis[ni][nj]) continue;

                if (a[ni][nj] < c) {
                    vis[ni][nj] = 1;
                    q.push({ni, nj, a[ni][nj]});
                }
            }
        }
    };

    int ans = 0;
    for (int pos = 0; pos < n * m; pos++) {
        auto [h, x, y] = pq[pos];
        if (vis[x][y]) continue;
        vis[x][y] = 1;

        go(h, x, y);
        ans++;
    }

    cout << ans << endl;
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
