#include <bits/stdc++.h>
using namespace std;

const uint64_t MOD = 1LL << 32;

typedef vector<uint64_t> vi;
typedef vector<vi> MAT;

MAT matmult(const MAT &a, const MAT &b) {
    int n = int(a.size());
    int m = int(b.size());
    int p = int(b[0].size());
    assert(a[0].size() == b.size());
    
    MAT c(n, vi(p, 0));
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < m; ++k) {
            for (int j = 0; j < p; ++j) {
                c[i][j] += a[i][k] * b[k][j];
                c[i][j] %= MOD;
            }
        }
    }
    return c;
}

MAT matexpo(MAT a, int64_t b) {
    int n = int(a.size());
    MAT res(n, vi(n, 0));
    for (int i = 0; i < n; ++i) res[i][i] = 1;
    while (b > 0) {
        if (b & 1) res = matmult(res, a);
        b >>= 1;
        a = matmult(a, a);
    }
    return res;
}

int dr[] = {1, 2, -1,  2, -2,  1, -2, -1};
int dc[] = {2, 1,  2, -1,  1, -2, -1, -2};

vector<pair<int,int>> destinations(int r, int c) {
    vector<pair<int,int>> dst;
    for (int i = 0; i < 8; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (nr >= 0 && nr < 8 && nc >= 0 && nc < 8) {
            dst.emplace_back(nr, nc);
        }
    }
    return dst;
}

void solve() {
    int k;
    cin >> k;
    // if we add a self-loop at the beginning to allow it to wait (since it's "AT MOST")
    // it will be able to come back, and wait not just at the beginning
    // so, we add another one (without any in-edges) with a self-loop
    // it can wait any amount of times, then go to the graph (and never comes back)
    MAT mat(65, vi(65));
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            for (auto [r, c]: destinations(i, j)) {
                mat[i*8+j][r*8+c] = 1;
            }
        }
    }
    // we can add edge only to begin and count k+1 paths, or add to every node and count k paths
    mat[64][0] = 1;     // edge to begin
    mat[64][64] = 1;    // self-loop
    MAT res = matexpo(mat, k + 1);
    int64_t ans = 0;
    for (int i = 0; i < 64; i++) {
        ans += res[64][i];
    }
    ans %= MOD;
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
