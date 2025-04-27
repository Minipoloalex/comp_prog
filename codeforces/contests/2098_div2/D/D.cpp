#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;
typedef vector<int64_t> vi;

const int MOD = int(1e9) + 7;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};


void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    auto inside = [&](int r, int c) {
        return r >= 1 && r <= n && c >= 1 && c <= m;
    };
    vector<ii> p(k + 1);
    for (auto &[x, y]: p) cin >> x >> y;
    vector<vector<vector<ii>>> g(n, vector<vector<ii>>(m));
    bool possible = true;
    for (int i = 0; i < k; i++) {
        auto &[x, y] = p[i];
        auto &[nx, ny] = p[i + 1];
        if (abs(nx - x) + abs(ny - y) != 2) {
            possible = false;
            break;
        }
        vector<ii> evens;  // max size 2
        for (int iii = 0; iii < 4; iii++) {
            int evenx = x + dx[iii];
            int eveny = y + dy[iii];

            if (!inside(evenx, eveny)) continue;
            for (int jj = 0; jj < 4; jj++) {
                int newx = evenx + dx[jj];
                int newy = eveny + dy[jj];
                if (inside(newx, newy) && nx == newx && ny == newy) {
                    evens.emplace_back(evenx - 1, eveny - 1); // 0-indexed in the graph
                }
            }
        }
        if (evens.size() == 2) {
            auto &[x1, y1] = evens[0];
            auto &[x2, y2] = evens[1];
            g[x1][y1].emplace_back(x2, y2);
            g[x2][y2].emplace_back(x1, y1);
        }
        else {
            assert(evens.size() == 1);
            auto &[x1, y1] = evens[0];
            g[x1][y1].emplace_back(x1, y1); // make sure |edges| = sum_i(edges_i) / 2
            g[x1][y1].emplace_back(x1, y1);
        }
    }
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    bool cycle = false, degen = false;
    function<ii(int,int,int,int)> dfs = [&](int x, int y, int px, int py) {
        vis[x][y] = true;
        ii ans = {1, g[x][y].size()};
        for (auto &[nx, ny]: g[x][y]) {
            if (nx == x && ny == y) {
                degen = true;
            }
            else if (px == nx && py == ny) {
                // parent
            }
            else if (!vis[nx][ny]) {
                auto [nodes, edges] = dfs(nx, ny, x, y);
                ans.first += nodes;
                ans.second += edges;
            }
            else {
                // not parent, but is visited: just detected a cycle
                cycle = true;
            }
        }
        return ans;
    };

    int64_t ans = 1;
    for (int x = 0; x < n && possible; x++) {
        for (int y = 0; y < m && possible; y++) {
            if (!g[x][y].empty() && !vis[x][y]) {
                cycle = false;
                degen = false;
                auto [nodes, edges] = dfs(x, y, -1, -1);
                assert(edges % 2 == 0);
                edges /= 2;
                // cout << nodes << " " << edges << " " << boolalpha << cycle << " " << degen << endl;
                if (edges > nodes) {
                    possible = false;
                }
                else {
                    if (cycle) {
                        (ans *= 2) %= MOD;
                    }
                    else if (!degen) {
                        // no cycle, and is not degen
                        assert(edges == nodes - 1);
                        (ans *= nodes) %= MOD;
                    }
                    // degen: *= 1
                }
            }
        }
    }
    if (!possible) ans = 0;
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
