#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

int SIZE = 4;
int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};

// int dr[] = {0, 0,  1, 1, 1, -1, -1, -1};
// int dc[] = {1,-1, -1, 0, 1, -1,  0,  1};


void print(vvi &g) {
    for (auto &v: g) {
        for (int val: v) {
            if (val == 1) {
                cout << "*";
            }
            else cout << ".";
        }
        cout << '\n';
    }
    cout << "\n\n\n";
}

void solve() {
    int n;
    cin >> n;
    // Trying to make: e.g. Circular: 140-150 not connect to 151-160

    vvi g(22*2, vi(360*2));
    for (int _ = 0; _ < n; _++) {
        char c;
        cin >> c;
        if (c == 'C') {
            int r, teta1, teta2;
            cin >> r >> teta1 >> teta2;
            r *= 2;
            teta1*=2;
            teta2*=2;
            if (teta1 <= teta2) {
                for (int i = teta1; i < teta2; i++) {
                    g[r][i] = 1;
                }
            }
            else {
                for (int i = teta1; i <= 719; i++) {
                    g[r][i] = 1;
                }
                for (int i = 0; i < teta2; i++) {
                    g[r][i] = 1;
                }
            }
        }
        else {
            assert(c == 'S');
            int r1, r2, teta;
            cin >> r1 >> r2 >> teta;
            teta *= 2;
            r1 *= 2;
            r2 *= 2;
            for (int i = r1; i < r2; i++) {
                g[i][teta] = 1;
            }
        }
    }
    // print(g);

    function<void(int,int)> dfs = [&](int r, int c) {
        g[r][c] = 1;
        for (int i = 0; i < SIZE; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nc < 0) {
                nc = nc + 720;
            }
            if (nc >= 720) {
                nc = 720 - nc;
            }
            if (nr >= 0 && nr <= 43 && g[nr][nc] == 0) {
                dfs(nr, nc);
            }
        }
    };
    dfs(0, 0);
    bool ans = g[43][0] == 1;
    cout << (ans ? "YES" : "NO") << '\n';
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
