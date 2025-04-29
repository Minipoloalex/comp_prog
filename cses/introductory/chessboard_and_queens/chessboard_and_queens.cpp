#include <bits/stdc++.h>
using namespace std;

void solve() {
    vector<string> board(8);
    for (auto &s: board) cin >> s;
    int mask_size = (1 << 8) - 1;
    function<int64_t(int, int, int, int)> go = [&](int r, int diag_mask1, int diag_mask2, int col_mask) -> int64_t {
        if (r == 8) return 1;

        int64_t ans = 0;
        for (int c = 0; c < 8; c++) {
            if (board[r][c] == '*' || (diag_mask1 & (1 << c)) || (diag_mask2 & (1 << c)) || (col_mask & (1 << c))) continue;

            int ndiag_mask1 = ((diag_mask1 | (1 << c)) >> 1) & mask_size;
            int ndiag_mask2 = ((diag_mask2 | (1 << c)) << 1) & mask_size;
            int ncol_mask = (col_mask | (1 << c)) & mask_size;
            ans += go(r + 1, ndiag_mask1, ndiag_mask2, ncol_mask);
        }
        return ans;
    };
    int64_t ans = go(0, 0, 0, 0);
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
