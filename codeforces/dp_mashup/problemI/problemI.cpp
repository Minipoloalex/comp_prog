#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<int>> mat(n, vector<int>(m));
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            cin >> mat[r][c];
        }
    }

    auto solve_row = [&](int r) -> int {
        int prev = 0;
        int curr;
        int ans = 0;
        for (int c = 0; c < m; c++) {
            if (mat[r][c] == 1) curr = prev + 1;
            else curr = 0;
            ans = max(ans, curr);
            prev = curr;
        }
        return ans;
    };

    vector<int> best(n, 0);

    for (int r = 0; r < n; r++) best[r] = solve_row(r);
    for (int i = 0; i < q; i++) {
        int r, c;
        cin >> r >> c;
        r--; c--;

        mat[r][c] ^= 1;
        best[r] = solve_row(r);

        int ans = 0;
        for (int ri = 0; ri < n; ri++) {
            ans = max(ans, best[ri]);
        }
        cout << ans << '\n';
    }
    return 0;
}
