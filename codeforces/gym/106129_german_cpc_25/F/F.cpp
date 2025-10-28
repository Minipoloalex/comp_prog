#include <bits/stdc++.h>
using namespace std;

const int MAX_SIZE = 2500;
int vis[MAX_SIZE+1][MAX_SIZE+1];

void solve() {
    int h, w;
    cin >> h >> w;
    vector<string> g(h);
    for (auto &s: g) cin >> s;
    int val = -1;
    for (int i = 0; i < h; i++) {
        int st = -1;
        int end = -1;
        for (int j = 0; j < w; j++) {
            if (g[i][j] == '#' && st == -1) {
                st = j;
            }
            if (g[i][j] == '#') {
                end = j;
            }
            if (st != -1 && g[i][j] != '#') {
                val = end - st + 1;
                break;
            }
        }
        if (st != -1) {
            val = end - st + 1;
            break;
        }
    }
    auto inside = [&](int i, int j) {
        return i >= 0 && i < h && j >= 0 && j < w;
    };
    auto valid = [&](int d) {
        memset(vis,0,sizeof(vis));
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (vis[i][j]) continue;
                if (g[i][j] == '#') {
                    for (int k = 0; k < d; k++) {
                        for (int l = 0; l < d; l++) {
                            int ni = i+k, nj = j+l;
                            if (!inside(ni, nj)) return false;
                            if (g[ni][nj] != '#') return false;
                            if (vis[ni][nj]) return false;

                            vis[ni][nj] = 1;
                        }
                    }
                }
            }
        }
        return true;
    };
    assert(val != -1);
    int ans = 1;
    for (int i = 1; 1LL * i * i <= val; i++) {
        if (val % i == 0) {
            if (valid(i)) {
                ans = max(ans, i);
            }
            if (valid(val / i)) {
                ans = max(ans, val / i);
            }
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
