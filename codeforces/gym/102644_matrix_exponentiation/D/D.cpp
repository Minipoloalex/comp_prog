#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = int64_t(1e9) + 7;

typedef vector<int64_t> vi;
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

MAT expo(MAT a, int64_t b) {
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

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    MAT mat(n, vi(n));
    while (m--) {
        int u, v;
        cin >> u >> v;
        u--;v--;
        mat[u][v]++;
    }
    MAT res = expo(mat, k);

    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans += res[i][j];
        }
        ans %= MOD;
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
