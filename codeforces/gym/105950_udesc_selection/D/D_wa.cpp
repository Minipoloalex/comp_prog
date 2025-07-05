#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    int ax, ay; cin >> ax >> ay;
    vector<vector<int64_t>> a(n + 1, vector<int64_t>(m + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }

    auto sp = [&] (int ix, int iy) -> int64_t {
        vector<int> dx = {0, 1, 0, -1};
        vector<int> dy = {1, 0, -1, 0};
        const int64_t inf = int64_t(1e12);

        vector<vector<int64_t>> d(n+1, vector<int64_t>(m+1, inf));
        d[ix][iy] = 0;

        set<array<int64_t, 3>> pq;
        pq.insert({0, ix, iy});

        while (!pq.empty()) {
            auto [cost, x, y] = *pq.begin();
            pq.erase(pq.begin());

            if (cost > d[x][y]) continue;

            for (int i = 0; i < 4; i++) {
                int64_t nx = x + dx[i];
                int64_t ny = y + dy[i];

                if (nx <= 0 || nx > n) continue;
                if (ny <= 0 || ny > m) continue;

                if ((cost | a[nx][ny]) < d[nx][ny]) {
                    pq.erase({ d[nx][ny], nx, ny });
                    d[nx][ny] = cost | a[nx][ny];
                    pq.insert({ d[nx][ny], nx, ny });
                }
            }
        }

        return d[n][m];
    };

    auto fs = sp(1, 1);
    auto ss = sp(ax, ay);

    cout << fs << ' ' << ss << endl;
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
