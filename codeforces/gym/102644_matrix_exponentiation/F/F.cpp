#include <bits/stdc++.h>
using namespace std;

typedef vector<int64_t> vi;
typedef vector<vi> MAT;

MAT matmult(const MAT &a, const MAT &b) {
    int n = int(a.size());
    int m = int(b.size());
    int p = int(b[0].size());
    assert(a[0].size() == b.size());

    MAT c(n, vi(p, INT64_MAX));
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < m; ++k) {
            for (int j = 0; j < p; ++j) {
                if (a[i][k] != INT64_MAX && b[k][j] != INT64_MAX) {
                    // over different k nodes, we want to minimize
                    c[i][j] = min(c[i][j], a[i][k] + b[k][j]);
                }
            }
        }
    }
    return c;
}

MAT matexpo(MAT a, int64_t b) {
    int n = int(a.size());

    // Note the unusual identity values
    MAT res(n, vi(n, INT64_MAX));
    for (int i = 0; i < n; ++i) res[i][i] = 0;

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
    MAT mat(n, vi(n, INT64_MAX));
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;b--;
        mat[a][b] = min<int64_t>(mat[a][b], c);
    }
    int64_t ans = INT64_MAX;    // 1e18 at most: k * c
    MAT res = matexpo(mat, k);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans = min<int64_t>(ans, res[i][j]);
        }
    }
    if (ans == INT64_MAX) {
        cout << "IMPOSSIBLE\n";
    }
    else {
        cout << ans << '\n';
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
