#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> mat(n, vector<int>(m));
    int mx = 0;
    int r = 0, c = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mat[i][j];
            if (mat[i][j] > mx) {
                mx = mat[i][j];
                r = i;
                c = j;
            }
        }
    }
    bool possible = true;
    int col = -1;
    // fix row r
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mat[i][j] == mx) {
                if (i == r) continue;
                if (col == j) continue;
                if (col == -1) {
                    col = j;
                }
                else {
                    possible = false;
                }
            }
        }
    }
    if (possible) {
        cout << mx - 1 << '\n';
        return;
    }
    int row = -1;
    possible = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mat[i][j] == mx) {
                if (j == c) continue;
                if (row == i) continue;
                if (row == -1) {
                    row = i;
                }
                else {
                    possible = false;
                }
            }
        }
    }
    if (possible) {
        mx--;
    }
    cout << mx << '\n';
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
