#include <bits/stdc++.h>
using namespace std;

int dp[(1 << 16)][17][17];
int mat[17][10010];

typedef pair<int, int> ii;
int follow_cost[16][16];
int wrap_around_cost[16][16];

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mat[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int min1 = INT_MAX, min2 = INT_MAX;

            if (i != j) {
                for (int c = 0; c < m; c++) {
                    int v1 = mat[i][c];
                    int v2 = mat[j][c];
                    min1 = min(min1, abs(v1 - v2));
                }
            }

            for (int c = 0; c < m - 1; c++) {
                int v1 = mat[i][c];
                int v2 = mat[j][c + 1];
                min2 = min(min2, abs(v1 - v2));
            }
            follow_cost[i][j] = min1;
            wrap_around_cost[i][j] = min2;
        }
    }

    memset(dp, -1, sizeof dp);

    // auto func = [&](int16_t which, int first, int prev, auto &&self) -> int {
    //     if (which == (1 << n) - 1) return INT_MAX;

    //     int &ans = dp[which][first][prev];
    //     if (ans != -1) return ans;

    //     int curr = 0;
    //     for (int nr = 0; nr < n; nr++) {
    //         if (!((1 << nr) & which)) {
    //             int16_t nstate = which | (1 << nr);
    //             if (first == -1) {
    //                 curr = max(curr, self(nstate, nr, nr, self)); 
    //             }
    //             else {
    //                 curr = max(curr, min(follow_cost[prev][nr], self(nstate, first, nr, self)));
    //             }
    //         }
    //     }
    //     ans = curr;
    //     return ans;
    // };

    auto func = [&](int which, int first, int prev, auto &&self) -> int {
        if (which == 0 || first == prev) return INT_MAX;

        int &ans = dp[which][first][prev];
        if (ans != -1) return ans;

        int curr = 0;
        for (int nr = 0; nr < n; nr++) {
            // row to select to be the next prev row
            // must not be prev (or first)
            if (((1 << nr) & which) && nr != prev && ((
                (first != nr || __builtin_popcount(which) == 2) // never select the first row, unless there is only that option
            ))) {
                int nstate = which - (1 << prev);   // remove prev from state
                int cost = follow_cost[nr][prev];
                // cout << cost << " ";
                curr = max(curr, min(self(nstate, first, nr, self), cost)); // new prev is nr
            }
        }
        ans = curr;
        return ans;
    };


    int ans = 0;
    for (int fst = 0; fst < n; fst++) {         // first row
        for (int prev = 0; prev < n; prev++) {  // prev here means last row
            if (fst == prev && n != 1) continue;    // fst == prev is possible only if n == 1

            // ans = max(ans, func(0, fst, prev, func));
            int min_follow_cost = func((1 << n) - 1, fst, prev, func);
            // cout << '\n' << '\n';
            int curr_wrap_around_cost = wrap_around_cost[prev][fst];

            // cout << fst << " " << prev << " " << min_follow_cost << " " << curr_wrap_around_cost << '\n' << '\n';

            ans = max(ans, min(curr_wrap_around_cost, min_follow_cost));
        }
    }
    cout << ans << '\n';
    return 0;
}
