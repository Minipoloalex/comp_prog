#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = int64_t(1e9) + 7;

typedef vector<int64_t> vi;
typedef vector<vi> MAT;

template<int SZ>
MAT matmult(const MAT &a, const MAT &b) {
    MAT res(SZ, vi(SZ));
    for (int i = 0; i < SZ; i++) {
        for (int k = 0; k < SZ; k++) {
            for (int j = 0; j < SZ; j++) {
                res[i][j] += a[i][k] * b[k][j];
                res[i][j] %= MOD;
            }
        }
    }
    return res;
}

void solve() {
    int64_t n;
    cin >> n;
    MAT ans = {{1, 0}, {0, 1}};
    MAT cur = {{19, 7}, {6, 20}};   // or swapped diagonals
    while (n) {
        if (n & 1) {
            ans = matmult<2>(ans, cur);
        }
        n >>= 1;
        cur = matmult<2>(cur, cur);
    }
    cout << ans[0][0] << '\n';
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
