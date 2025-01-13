#include <bits/stdc++.h>
using namespace std;

int n;
const int MAX = 20;

char grid[MAX][MAX];
int vis[MAX][MAX];

int dy[] = {0, 0, 1, -1};
int dx[] = {1, -1, 0, 0};

bool inside(int x, int y, int xi, int xf, int yi, int yf) {
    return x >= xi && x <= xf && y >= yi && y <= yf;
}

void dfs(int x, int y, int xi, int xf, int yi, int yf) {
    vis[y][x] = 1;
    char c = grid[y][x];
    for (int i = 0; i < 4; i++) {
        int ny = y + dy[i];
        int nx = x + dx[i];
        if (inside(nx, ny, xi, xf, yi, yf) && !vis[ny][nx] && grid[ny][nx] == c) {
            dfs(nx, ny, xi, xf, yi, yf);
        }
    }
}

int cnt[26];
bool pcp(tuple<int,int,int,int> &t) {
    auto &[xi, xf, yi, yf] = t;
    memset(vis, 0, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    for (int x = xi; x <= xf; x++) {
        for (int y = yi; y <= yf; y++) {
            if (!vis[y][x]) {
                char c = grid[y][x];
                cnt[c - 'A']++;
                dfs(x, y, xi, xf, yi, yf);
            }
        }
    }

    int cols = 0;
    bool found_2plus = false, found1 = false;
    for (int i = 0; i < 26; i++) {
        if (cnt[i] >= 2) {
            found_2plus = true;
        }
        else if (cnt[i] == 1) {
            found1 = true;
        }
        cols += cnt[i] > 0;
    }
    return cols == 2 && found1 && found_2plus;
}

void solve() {    
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }
    vector<tuple<int,int,int,int>> pcps;
    for (int xi = 0; xi < n; xi++) {
        for (int xf = xi; xf < n; xf++) {
            for (int yi = 0; yi < n; yi++) {
                for (int yf = yi; yf < n; yf++) {
                    auto t = make_tuple(xi, xf, yi, yf);
                    if (pcp(t)) {
                        pcps.push_back(t);
                    }
                }
            }
        }
    }
    auto subset = [&](int i, int j) -> bool {
        auto &[xi, xf, yi, yf] = pcps[i];
        auto &[oxi, oxf, oyi, oyf] = pcps[j];

        return xi >= oxi && xf <= oxf && yi >= oyi && yf <= oyf;
    };

    int ans = 0;
    for (int i = 0; i < (int) pcps.size(); i++) {
        bool issub = false;
        for (int j = 0; j < (int) pcps.size(); j++) {
            if (i == j) continue;
            if (subset(i, j)) {
                issub = true;
                break;
            }
        }
        if (!issub) ans++;
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    freopen("where.in","r",stdin);
    freopen("where.out","w",stdout);
    solve();
    return 0;
}
