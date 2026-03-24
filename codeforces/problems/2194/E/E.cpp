#include <bits/stdc++.h>
using namespace std;

using vi = vector<int64_t>;
using vvi = vector<vi>;

void print(vvi v) {
    for (auto &a: v) {
        for (auto &val: a) {
            cout << val << " ";
        }
        cout << '\n';
    }
    cout << endl;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    vvi dpto(n, vi(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int64_t cur = (i > 0 || j > 0) ? INT64_MIN : 0;
            if (i > 0) cur = max(cur, dpto[i-1][j]);
            if (j > 0) cur = max(cur, dpto[i][j-1]);
            dpto[i][j] = a[i][j] + cur;
        }
    }
    vvi dpfrom(n, vi(m));
    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            int64_t cur = (i + 1 < n || j + 1 < m) ? INT64_MIN : 0;
            if (i + 1 < n) cur = max(cur, dpfrom[i+1][j]);
            if (j + 1 < m) cur = max(cur, dpfrom[i][j+1]);
            dpfrom[i][j] = a[i][j] + cur;
        }
    }
    vvi prow(n, vi(m+1, INT64_MIN));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int64_t val = dpfrom[i][j] + dpto[i][j] - a[i][j];
            prow[i][j+1] = max(prow[i][j], val);
        }
    }
    vvi pcol(m, vi(n+1, INT64_MIN));
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            int64_t val = dpfrom[i][j] + dpto[i][j] - a[i][j];
            pcol[j][i+1] = max(pcol[j][i], val);
        }
    }
    int64_t baseans = dpfrom[0][0] + dpto[0][0] - a[0][0];  // candidate path
    int64_t ans = baseans;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int64_t val = dpfrom[i][j] + dpto[i][j] - a[i][j];
            if (val == baseans) {   // in the best path
                int64_t cur = baseans - a[i][j]*2;  // consider still using the same path
                // consider never taking this position
                int nxtcol = j+1;
                int prvrow = i-1;
                if (nxtcol < m && prvrow >= 0) {
                    cur = max(cur, pcol[nxtcol][prvrow+1]);
                }
                int prvcol = j-1;
                int nxtrow = i+1;
                if (prvcol >= 0 && nxtrow < n) {
                    cur = max(cur, prow[nxtrow][prvcol+1]);
                }
                ans = min(ans, cur);
            }
        }
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
