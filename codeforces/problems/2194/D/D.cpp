#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> mat(n, vector<int>(m));
    vector<int> row(n);
    int sm = 0;
    for (int i = 0; i < n; i++) {
        for (auto &x: mat[i]) cin >> x;
        row[i] = accumulate(mat[i].begin(), mat[i].end(), 0);
        sm += row[i];
    }
    int64_t ans = int64_t(sm / 2) * ((sm + 1) / 2);
    int want = sm / 2;
    int cur = 0;

    string s;
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (cur == want) {
            s += "D"; // assumes last column already
        }
        else if (cur + row[i] >= want) {
            int wantrow = want - cur;
            int remrow = row[i] - wantrow;
            int currow = 0;
            while (currow < remrow && j < m) {
                currow += mat[i][j++];
                s += "R";
            }
            s += "D";
            while (j < m) {
                cur += mat[i][j++];
                s += "R";
            }
            assert(cur == want);
        }
        else {
            cur += row[i];
            s += "D";
        }
    }
    // treats edge-case: all 0s (or all 0s and one 1)
    s += string(m - j, 'R');
    cout << ans << '\n' << s << '\n';
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
