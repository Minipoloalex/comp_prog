#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = int64_t(1e9) + 7;

template<typename T, int SZ>
struct MAT {
    vector<vector<T>> mat;
    static const MAT iden;
    MAT(): mat(SZ, vector<T>(SZ, T(0))) {}
    MAT operator*(const MAT &other) const {
        MAT res;
        for (int i = 0; i < SZ; i++) {
            for (int k = 0; k < SZ; k++) {
                for (int j = 0; j < SZ; j++) {
                    res.mat[i][j] += mat[i][k] * other.mat[k][j];
                    res.mat[i][j] %= MOD;
                }
            }
        }
        return res;
    }
    MAT expo(int64_t n) const {
        MAT b = *this;
        MAT res = iden;
        while (n) {
            if (n & 1) {
                res = res * b;
            }
            n >>= 1;
            b = b * b;
        }
        return res;
    }
};
template<typename T, int SZ>
const MAT<T, SZ> MAT<T, SZ>::iden = [] {
    MAT<T, SZ> I;
    for (int i = 0; i < SZ; ++i) I.mat[i][i] = T(1);
    return I;
}();

void solve() {
    int64_t n;
    cin >> n;
    MAT<int64_t,2> fib;
    fib.mat = {{1, 1}, {1, 0}};
    MAT<int64_t,2> res = fib.expo(n);

    // same thing
    cout << res.mat[1][0] << '\n';
    // cout << res.mat[0][1] << '\n';
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
