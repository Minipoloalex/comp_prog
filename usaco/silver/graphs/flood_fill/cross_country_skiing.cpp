#include <bits/stdc++.h>
using namespace std;

int m, n;

int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};

const int MAX = 500;

int grid[MAX + 1][MAX + 1];
int vis[MAX + 1][MAX + 1];
int w[MAX + 1][MAX + 1];

bool inside(int r, int c) {
    return r >= 0 && r < m && c >= 0 && c < n;
}

int dfs(int r, int c, int lmt) {
    vis[r][c] = 1;
    int ans = w[r][c];
    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        int diff = abs(grid[r][c] - grid[nr][nc]);
        if (inside(nr, nc) && !vis[nr][nc] && diff <= lmt) {
            ans += dfs(nr, nc, lmt);
        }
    }
    return ans;
}

void solve() {
    cin >> m >> n;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }
    int w0r = -1, w0c = -1, wcnt = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> w[i][j];
            if (w[i][j] == 1) {
                w0r = i;
                w0c = j;
                wcnt++;
            }
        }
    }

    auto possible = [&](int med) -> bool {
        memset(vis, 0, sizeof(vis));
        int ans = dfs(w0r, w0c, med);
        return ans == wcnt;
    };

    if (wcnt == 0) {
        cout << "0\n";
        return;
    }
    int lo = 0, hi = int(1e9);
    while (lo < hi) {
        int med = lo + (hi - lo) / 2;
        if (possible(med)) {
            hi = med;
        }
        else {
            lo = med + 1;
        }
    }
    cout << lo << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    freopen("ccski.in", "r", stdin);
    freopen("ccski.out", "w", stdout);
    solve();
    return 0;
}
