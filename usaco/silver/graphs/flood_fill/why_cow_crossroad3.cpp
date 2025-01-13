#include <bits/stdc++.h>
using namespace std;

int n;
const int MAX_N = 100;
int vis[MAX_N][MAX_N];
int cow[MAX_N][MAX_N];

set<pair<int,int>> roads[MAX_N][MAX_N];
int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};

bool inside(int r, int c) {
    return r >= 0 && r < n && c >= 0 && c < n;
}
bool can(int r, int c, int nr, int nc) {
    return roads[r][c].find({nr, nc}) == roads[r][c].end();
}

int dfs(int r, int c) {
    vis[r][c] = 1;
    int ans = cow[r][c];
    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (inside(nr, nc) && !vis[nr][nc] && can(r, c, nr, nc)) {
            ans += dfs(nr, nc);
        }
    }
    return ans;
}

void solve() {
    int K, R;
    cin >> n >> K >> R;
    while (R--) {
        int r, c, ar, ac;
        cin >> r >> c >> ar >> ac;
        r--;c--;ar--;ac--;
        roads[r][c].emplace(ar, ac);
        roads[ar][ac].emplace(r, c);
    }
    vector<pair<int,int>> cows(K);
    for (auto &[r, c]: cows) {
        cin >> r >> c;
        r--;c--;
        cow[r][c] = 1;  // each cow is in a != field
    }

    memset(vis, 0, sizeof(vis));
    int64_t ans = 0;    // not required (50 * 50 = 2500)
    for (auto &[r, c]: cows) {
        if (!vis[r][c]) {
            int seen = dfs(r, c);
            int others = K - seen;
            ans += seen * 1LL * others;
        }
    }
    cout << ans / 2 << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    freopen("countcross.in", "r", stdin);
    freopen("countcross.out", "w", stdout);
    solve();
    return 0;
}
