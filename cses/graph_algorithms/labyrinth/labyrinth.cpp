#include <bits/stdc++.h>
using namespace std;

int dr[] = {1, -1, 0, 0};
int dc[] = {0, 0, 1, -1};
char ch[] = {'D', 'U', 'R', 'L'};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    for (auto &s: g) cin >> s;
    auto inside = [&](int r, int c) {
        return r >= 0 && r < n && c >= 0 && c < m;
    };
    vector<vector<int>> dist(n, vector<int>(m, -1));
    vector<vector<tuple<int,int,char>>> par(n, vector<tuple<int,int,char>>(m, {-1, -1, 0}));

    auto bfs = [&](int r, int c) {
        deque<pair<int,int>> q = {{r, c}};
        dist[r][c] = 0;
        while (!q.empty()) {
            auto [ru, cu] = q.front();
            q.pop_front();
            for (int i = 0; i < 4; i++) {
                int nr = ru + dr[i];
                int nc = cu + dc[i];
                if (inside(nr, nc) && dist[nr][nc] == -1 && g[nr][nc] != '#') {
                    dist[nr][nc] = dist[ru][cu] + 1;
                    q.emplace_back(nr, nc);
                    par[nr][nc] = make_tuple(ru, cu, ch[i]);
                }
            }
        }
    };
    pair<int,int> s, d;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] == 'A') s = make_pair(i, j);
            else if (g[i][j] == 'B') d = make_pair(i, j);
        }
    }
    bfs(s.first, s.second);
    int dd = dist[d.first][d.second];
    if (dd == -1) {
        cout << "NO\n";
    }
    else {
        cout << "YES\n";
        auto [cr, cc, dir] = par[d.first][d.second];
        cout << dd << '\n';
        string dirs;
        while (cr != -1) {
            dirs += dir;
            tie(cr, cc, dir) = par[cr][cc];
        }
        reverse(dirs.begin(), dirs.end());
        cout << dirs << '\n';
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
