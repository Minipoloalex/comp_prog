#include <bits/stdc++.h>
using namespace std;

int dx[4] = {0, 1, -1, 0};
int dy[4] = {1, 0, 0, -1};

int main() {
    cin.tie(NULL)->ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> a(n, vector<int>(m, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> a[i][j];
            }
        }
        auto get_neighbours = [&](int i, int j) {
            vector<pair<int, int>> res;
            for (int k = 0; k < 4; k++) {
                int r = i + dy[k];
                int c = j + dx[k];
                if (r >= 0 && r < n && c >= 0 && c < m) {
                    res.emplace_back(r, c);
                }
            }
            return res;
        };
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int value = a[i][j];
                bool is_greater = true;
                int maximum = 0;
                for (auto &[r, c]: get_neighbours(i, j)) {
                    // cout << r << " " << c << endl;
                    if (a[r][c] >= value) {
                        is_greater = false;
                    }
                    else {
                        maximum = max(maximum, a[r][c]);
                    }
                }
                if (is_greater) {
                    a[i][j] = maximum;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << a[i][j] << " ";
            }
            cout << '\n';
        }
    }
    return 0;
}
