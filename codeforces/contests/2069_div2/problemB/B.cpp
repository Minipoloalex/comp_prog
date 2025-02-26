#include <bits/stdc++.h>
using namespace std;

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m, 0));
    vector<int> mp(n * m, 0);
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            cin >> grid[r][c];
            grid[r][c]--;
            mp[grid[r][c]] = 1;
        }
    }
    auto inside = [n, m](int r, int c) {
        return r >= 0 && r < n && c >= 0 && c < m;
    };
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            for (int i = 0; i < 4; i++) {
                int nr = r + dy[i];
                int nc = c + dx[i];
                if (inside(nr, nc) && grid[r][c] == grid[nr][nc]) {
                    mp[grid[r][c]] = 2;
                }
            }
        }
    }
    int mx = *max_element(mp.begin(), mp.end());
    int ans = 0;
    for (int i = 0; i < n * m; i++) {
        ans += mp[i];
    }
    ans -= mx;
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
