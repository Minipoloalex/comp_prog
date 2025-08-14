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
    int n;
    int64_t k;
    cin >> n >> k;
    vector<int64_t> a(n);
    for (auto &ai: a) cin >> ai;
    MAT mat(n, vi(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int64_t v = a[i] ^ a[j];
            int ones = __builtin_popcountll(v);
            if (ones % 3 == 0) {
                mat[i][j] = 1;
            }
        }
    }
    MAT res = mat_expo(mat, k - 1);
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
