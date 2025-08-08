#include <bits/stdc++.h>
using namespace std;

int dr[] = {1, -1, 0, 0};
int dc[] = {0, 0, 1, -1};
map<char, int> dir = {
    {'D', 0},
    {'U', 1},
    {'R', 2},
    {'L', 3},
};

void solve() {
    int n, m;
    cin >> n >> m;
    auto inside = [&](int r, int c) {
        return r >= 0 && r < n && c >= 0 && c < m;
    };

    vector<string> g(n);
    for (auto &s: g) cin >> s;
    auto get_dir = [&](int r, int c) -> int {
        assert(g[r][c] != '?');
        int idx = dir[g[r][c]];
        return idx;
    };

    using vpii = vector<pair<int,int>>;
    using vvpii = vector<vpii>;
    vector<vvpii> rev(n, vvpii(m));
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            if (g[r][c] != '?') {
                int idx = get_dir(r, c);
                int nr = r + dr[idx];
                int nc = c + dc[idx];
                if (inside(nr, nc)) {
                    rev[nr][nc].emplace_back(r, c);
                }
            }
        }
    }

    queue<pair<int,int>> q;
    vector<vector<bool>> outside(n, vector<bool>(m, false));
    auto insert = [&](int r, int c) {
        outside[r][c] = true;
        q.emplace(r, c);
    };
    for (int r = 0; r < n; r++) {
        if (g[r][0] == 'L') {
            insert(r, 0);
        }
        if (g[r][m - 1] == 'R') {
            insert(r, m - 1);
        }
    }
    for (int c = 0; c < m; c++) {
        if (g[0][c] == 'U') {
            insert(0, c);
        }
        if (g[n - 1][c] == 'D') {
            insert(n - 1, c);
        }
    }

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        for (auto &[nr, nc]: rev[r][c]) {
            if (inside(nr, nc) && !outside[nr][nc]) {
                assert(g[nr][nc] != '?');   // because it's the reversed graph
                outside[nr][nc] = true;
                q.emplace(nr, nc);
            }
        }
    }

    int ans = 0;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            if (g[r][c] == '?') {
                bool all = true;
                for (int i = 0; i < 4; i++) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];
                    if (inside(nr, nc) && !outside[nr][nc]) {
                        all = false;
                    }
                }
                if (!all) {
                    ans++;
                }
            }
            else {
                if (!outside[r][c]) {
                    ans++;
                }
            }
        }
    }
    cout << ans << '\n';
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
