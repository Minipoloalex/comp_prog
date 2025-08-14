#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = int64_t(1e9);

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
MAT mat_expo(MAT a, int64_t b) {
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
    int k;
    cin >> k;
    vector<int> b(k), c(k);
    for (auto &bi: b) cin >> bi;
    for (auto &ci: c) cin >> ci;
    int n;
    cin >> n;
    MAT mat(k, vi(k));
    for (int i = 0; i < k; i++) {
        mat[k - 1][i] = c[k - 1 - i];
    }
    for (int i = 0; i < k - 1; i++) {
        mat[i][i + 1] = 1;
    }
    MAT first(k, vi(1));
    for (int i = 0; i < k; i++) {
        first[i][0] = b[i];
    }
    MAT res = mat_expo(mat, n - 1); // since we're working 0-indexed
    MAT ans = matmult(res, first);
    cout << ans[0][0] << '\n';
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
