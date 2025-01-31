#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
vector<vi> pts_costs;
int n, k;

const int inf = int(1e8);

int dp[1010][110];

int solve_dp(int i, int pts_left) {
    if (i == n) {
        return pts_left == 0 ? 0: inf;
    }

    int &ans = dp[i][pts_left];
    if (ans != -1) return ans;

    vi &pts = pts_costs[i];
    int curr = INT_MAX;
    for (int p = 0; p < (int) pts.size() && pts_left - p >= 0; p++) {   // if negative, then we do not want
        int after = solve_dp(i + 1, pts_left - p);
        if (after < inf) {
            curr = min(curr, after + pts[p]);
        }
    }
    return ans = curr;
}


int main() {
    cin.tie(0)->ios::sync_with_stdio(0);

    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        cin >> n >> k;
        pts_costs.assign(n, vi());
        memset(dp, -1, sizeof(dp));
        for (int i = 0; i < n; i++) {
            int wi, hi;
            cin >> wi >> hi;
            vi &pc = pts_costs[i];
            pc.assign(wi + hi + 1, INT_MAX);
            for (int r = 0; r <= hi; r++) {
                for (int c = 0; c <= wi; c++) {
                    pc[r + c] = min(pc[r + c], r * wi + (hi - r) * c);
                }
            }
            // for (int p = 0; p < wi + hi + 1; p++) {
            //     cout << pc[p] << " ";
            // }
            // cout << endl;
        }
        int ans = solve_dp(0, k);
        if (ans < inf) cout << ans << '\n';
        else cout << "-1\n";
    }
    return 0;
}
