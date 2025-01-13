#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1000;
char grid[MAX_N + 1][MAX_N + 1];
int vis[MAX_N + 1][MAX_N + 1];

int n;

int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};

bool inside(int r, int c) {
    return r >= 0 && r < n && c >= 0 && c < n;
}

pair<int,int> dfs(int r, int c) {
    vis[r][c] = 1;
    int area = 1, perim = 0;
    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (inside(nr, nc)) {
            if (!vis[nr][nc] && grid[nr][nc] == '#') {
                auto [a, p] = dfs(nr, nc);
                area += a;
                perim += p;
            }
            else if (grid[nr][nc] == '.') {
                perim++;
            }
        }
        else {
            perim++;
        }
    }
    return make_pair(area, perim);
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }
    memset(vis, 0, sizeof(vis));
    int area = 0, perim = 0;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (!vis[r][c] && grid[r][c] == '#') {
                auto [a, p] = dfs(r, c);
                if (a > area || (a == area && p < perim)) {
                    area = a;
                    perim = p;
                }
            }
        }
    }
    cout << area << " " << perim << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    freopen("perimeter.in", "r", stdin);
    freopen("perimeter.out", "w", stdout);
    solve();
    return 0;
}
