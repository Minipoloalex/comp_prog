#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = 1e9;
 
class MatrixPow {
public:

    vector<vector<int64_t>> mat;
    int n;
 
    vector<vector<int64_t>> mult(vector<vector<int64_t>>& a, vector<vector<int64_t>>& b) {
        vector<vector<int64_t>> res(n, vector<int64_t>(n, 0));
        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)
                for(int k=0;k<n;++k)
                {
                    res[i][j] += (a[i][k] * b[k][j]);
                    if (res[i][j] >= MOD) res[i][j] %= MOD;
                }
        return res;
    }
 
    MatrixPow(vector<vector<int64_t>>& m) : mat(m), n(m.size()) {}
 
    vector<vector<int64_t>> pow(int64_t exp) {
        vector<vector<int64_t>> res(n, vector<int64_t>(n, 0));
        for(int i=0;i<n;++i) res[i][i] = 1;
        while (exp > 0) {
            if (exp & 1) res = mult(res, mat);
            mat = mult(mat, mat);
            exp >>= 1;
        }
        return res;
    }
};



void solve(int &cur,int i, int nova,int &n,vector<vector<int64_t>> &mat)
{
    if(i>n)
        return;
    if(i==n)
    {
        mat[cur][nova]++;
        return;
    }
    if(cur&(1<<i))
        solve(cur,i+1,nova,n,mat);
    else
    {
        solve(cur, i + 1, nova, n, mat);
        solve(cur, i + 1, nova | (1 << i), n, mat);
        if (i + 1 < n && ((cur & (1 << (i + 1))) == 0)) {
            solve(cur, i + 2, nova, n, mat);
        }
    }
}

void solve_stuff() {
    int n; int64_t m;
    cin >> n >> m;
    vector<vector<int64_t>> mat(1<<n, vector<int64_t>(1<<n));
    for (int mask = 0; mask < (1 << n); mask++) {
        solve(mask, 0, 0, n, mat);
    }
    // for (auto &v: mat) {
    //     for (auto &val: v) {
    //         cout << val << " ";
    //     }
    //     cout << '\n';
    // }
    MatrixPow mpow(mat);
    vector<vector<int64_t>> res = mpow.pow(m);
    cout << res[0][0] << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve_stuff();
    }
    return 0;
}
