#include <bits/stdc++.h>
using namespace std;

const int MAX = int(1e3);
int vis[MAX + 10][MAX + 10];
char g[MAX + 10][MAX + 10];

int dc[] = {0, 0, 1, -1};
int dr[] = {1, -1, 0, 0};

int n, m;

bool inside(int nr, int nc) {
    return nr >= 0 && nr < n && nc >= 0 && nc < m;
}

void dfs(int r, int c) {
    vis[r][c] = 1;
    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (inside(nr, nc) && !vis[nr][nc] && g[nr][nc] == '.') {
            dfs(nr, nc);
        }
    }
}

void solve() {
    cin >> n >> m;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            cin >> g[r][c];
        }
    }
    int ans = 0;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            if (!vis[r][c] && g[r][c] == '.') {
                ans++;
                dfs(r, c);
            }
        }
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
