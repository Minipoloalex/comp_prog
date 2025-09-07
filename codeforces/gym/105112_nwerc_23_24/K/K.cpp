#include <bits/stdc++.h>
using namespace std;

int dx[] = {1, 1, -1, -1};
int dy[] = {-1, 1, 1, -1};

void solve() {
    int n, a, b, c, d;
    cin >> n >> a >> b >> c >> d;
    auto neigh = [&](int x, int y, int A, int B) {
        vector<pair<int,int>> ans;
        for (int i = 0; i < 4; i++) {
            ans.emplace_back(x + dx[i] * A, y + dy[i] * B);
            ans.emplace_back(x + dx[i] * B, y + dy[i] * A);
        }
        return ans;
    };
    auto inside = [&](int x, int y) {
        return x >= 0 && x < n && y >= 0 && y < n;
    };

    vector<vector<array<int,2>>> vis(n, vector<array<int,2>>(n, {0,0}));
    queue<array<int,3>> q;
    vis[0][0][0] = 1;
    vis[0][0][1] = 1;

    for (auto [nx, ny]: neigh(0, 0, a, b)) {
        if (inside(nx, ny)) {
            vis[nx][ny][0] = 1;
            q.push({nx, ny, 0});
        }
    }
    for (auto [nx, ny]: neigh(0, 0, c, d)) {
        if (inside(nx, ny)) {
            vis[nx][ny][1] = 1;
            q.push({nx, ny, 1});
        }
    }

    while (!q.empty()) {
        auto [x, y, prv] = q.front();
        q.pop();
        int nxt = 1 - prv;

        int A, B;
        if (prv == 1) {
            A = a;
            B = b;
        }
        else {
            A = c;
            B = d;
        }
        for (auto [nx, ny]: neigh(x, y, A, B)) {
            if (inside(nx, ny) && !vis[nx][ny][nxt]) {
                vis[nx][ny][nxt] = 1;
                q.push({nx, ny, nxt});
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (vis[i][j][0] || vis[i][j][1]) ans++;
        }
    }
    cout << ans << '\n';
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
