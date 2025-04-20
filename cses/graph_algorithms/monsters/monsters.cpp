#include <bits/stdc++.h>
using namespace std;

int dc[] = {1, -1, 0, 0};
int dr[] = {0, 0, 1, -1};
char ch[] = {'R', 'L', 'D', 'U'};
typedef tuple<int,int,char> mytp;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    for (auto &s: g) cin >> s;
    auto inside = [&](int r, int c) {
        return r >= 0 && r < n && c >= 0 && c < m;
    };
    auto bfs = [&](vector<pair<int,int>> ss, vector<vector<int>> &dist, vector<vector<mytp>> &par) {
        queue<pair<int,int>> q;
        for (auto &p: ss) {
            q.push(p);
            dist[p.first][p.second] = 0;
        }
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                int chr = ch[i];
                if (inside(nr, nc) && g[nr][nc] != '#' && dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    par[nr][nc] = make_tuple(r, c, chr);
                    q.emplace(nr, nc);
                }
            }
        }
    };
    vector<vector<int>> distmonsters(n, vector<int>(m, -1));
    vector<vector<int>> distme(n, vector<int>(m, -1));
    vector<vector<mytp>> _(n, vector<mytp>(m, {-1,-1,0}));
    vector<vector<mytp>> par(n, vector<mytp>(m, {-1,-1,0}));

    vector<pair<int,int>> monsters;
    pair<int,int> st;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] == 'M') {
                monsters.emplace_back(i, j);
            }
            else if (g[i][j] == 'A') {
                st = {i, j};
            }
        }
    }

    bfs(monsters, distmonsters, _);
    bfs({st}, distme, par);

    bool ans = false;
    pair<int,int> end;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0 || j == 0 || i == n - 1 || j == m - 1) {
                // end
                if (g[i][j] != '#' && distme[i][j] != -1 && 
                    (distme[i][j] < distmonsters[i][j] || distmonsters[i][j] == -1)) {
                    ans = true;
                    end = {i, j};
                }
            }
        }
    }
    cout << (ans ? "YES" : "NO") << '\n';
    if (ans) {
        string path;
        auto [cur_r, cur_c, cur_dir] = par[end.first][end.second];
        while (cur_r != -1) {
            path += cur_dir;
            tie(cur_r, cur_c, cur_dir) = par[cur_r][cur_c];
        }
        reverse(path.begin(), path.end());
        cout << path.size() << '\n';
        cout << path << '\n';
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
