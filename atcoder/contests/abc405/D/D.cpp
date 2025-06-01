#include <bits/stdc++.h>
using namespace std;

int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};
// char ch[] = {'>', '<', 'v', '^'};
char opposite[] = {'<', '>', '^', 'v'};

void solve() {
    int h, w;
    cin >> h >> w;
    vector<string> g(h);
    for (auto &s: g) cin >> s;

    vector<pair<int,int>> pos;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (g[i][j] == 'E') {
                pos.emplace_back(i, j);
            }
        }
    }
    auto inside = [&](int r, int c) {
        return r >= 0 && r < h && c >= 0 && c < w;
    };
    queue<pair<int,int>> q;
    for (auto &p: pos) q.push(p);
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (inside(nr, nc) && g[nr][nc] == '.') {
                g[nr][nc] = opposite[i];
                q.emplace(nr, nc);
            }
        }
    }
    for (string &s: g) {
        cout << s << '\n';
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
