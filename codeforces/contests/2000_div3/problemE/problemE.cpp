#include <bits/stdc++.h>
using namespace std;


/**
 * @brief Initially, I went with a constructive algorithm determining the contribution of the rows and columns iteratively
 * But the solution of independently calculating the (i, j) contribution from rows and columns is much better.
 * 
 * @return int 
 */
int main() {
    cin.tie(0)->ios::sync_with_stdio(0);

    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        int n, m, k;
        cin >> n >> m >> k;
        int w;
        cin >> w;
        vector<int> a(w);
        for (int i = 0; i < w; i++) cin >> a[i];
        sort(a.rbegin(), a.rend());

        vector<tuple<int, int, int>> positions;
        for (int r = 0; r < n; r++) {
            int rdist_to_end = n - r - 1;
            int rdist_to_begin = r;
            int rmin_dist = min(rdist_to_begin, rdist_to_end) + 1;

            int rmax_possible = min(n - k + 1, k);
            int curr_row = min(rmin_dist, rmax_possible);

            for (int c = 0; c < m; c++) {
                int cdist_to_end = m - c - 1;
                int cdist_to_begin = c;
                int cmin_dist = min(cdist_to_begin, cdist_to_end) + 1;

                int cmax_possible = min(m - k + 1, k);
                int curr_col = min(cmin_dist, cmax_possible);

                positions.emplace_back(curr_row * curr_col, r, c);
            }
        }

        sort(positions.rbegin(), positions.rend());
        int64_t ans = 0;
        for (int i = 0; i < w; i++) {
            auto &[weight, r, c] = positions[i];
            ans += (int64_t) weight * a[i];
        }
        cout << ans << '\n';
    }
    return 0;
}
