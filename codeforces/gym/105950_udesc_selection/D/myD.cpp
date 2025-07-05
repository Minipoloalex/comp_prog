#include <bits/stdc++.h>
using namespace std;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

// This is my implementation, same as D.cpp (my teammates solved D during the virtual contest)

void solve() {
    int n, m, xx, yy;
    cin >> n >> m >> xx >> yy;
    xx--;yy--;
    vector<vector<int>> g(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> g[i][j];
        }
    }
    auto distance = [&](int stx, int sty, int64_t mask) { // could just return true or false (no need for distance)
        vector<vector<int>> dist(n, vector<int>(m, -1)); // could be just vis (bool)
        queue<tuple<int,int>> q;
        dist[stx][sty] = 0;
        q.emplace(stx, sty);
        while (!q.empty()) {
            auto &[x, y] = q.front();
            q.pop();
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m || dist[nx][ny] != -1) continue;
                if ((g[nx][ny] | mask) != mask) continue;

                dist[nx][ny] = dist[x][y] | g[nx][ny];
                q.emplace(nx, ny);
            }
        }
        return dist[n-1][m-1];
    };
    auto shortest = [&](int stx, int sty) {
        int64_t mask = (1LL << 32) - 1;
        for (int i = 31; i >= 0; i--) {
            mask ^= 1LL << i;
            if (distance(stx, sty, mask) == -1) {    // if not possible, needs to be 1
                mask ^= 1LL << i;
            }
        }
        return mask;    // same as returning distance(stx, sty, mask)
    };
    int d1 = shortest(0, 0);
    int d2 = shortest(xx, yy);
    cout << d1 << " " << d2 << '\n';
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
