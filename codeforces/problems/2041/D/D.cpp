#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;

int dx[] = {1, -1, 0, 0};   // r
int dy[] = {0, 0, 1, -1};   // c
int ddir[] = {0, 1, 2, 3};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    for (auto &s: g) cin >> s;
    auto inside = [&](int r, int c) {
        return r >= 0 && r < n && c >= 0 && c < m;
    };
    array<int,2> st;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] == 'S') {
                st = {i, j};
            }
        }
    }

    // no need for enhanced dijkstra, can just use enhanced BFS (with more states)
    // basically the vertices are defined by (x, y, dir, mov)
    vector<vvvi> dist(n, vvvi(m, vvi(4, vi(4, INT_MAX))));
    queue<array<int,5>> q;
    q.push({0, 0, 0, st[0], st[1]});
    while (!q.empty()) {
        auto [d, dir, mov, x, y] = q.front();
        q.pop();
        if (g[x][y] == 'T') {
            cout << d << '\n';
            return;
        }
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            int ndir = ddir[i];
            if (inside(nx, ny) && g[nx][ny] != '#') {
                if (ndir != dir) {
                    auto &dst = dist[nx][ny][ndir][1];
                    if (dst == INT_MAX) {
                        dst = d + 1;
                        q.push({dst, ndir, 1, nx, ny});
                    }
                }
                else {
                    // ndir == dir
                    if (mov < 3) {
                        int nmov = mov + 1;
                        auto &dst = dist[nx][ny][ndir][nmov];
                        if (dst == INT_MAX) {
                            dst = d + 1;
                            q.push({dst, ndir, nmov, nx, ny});
                        }
                    }
                }
            }
        }
    }
    cout << "-1\n";
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
