#include <bits/stdc++.h>
using namespace std;

const int MAX_N = int(1e4) + 10;
const int MAX_K = int(1e3) + 10;

// 1e4 * 1e5 = 1e9 -> can use int
int dp[MAX_N][MAX_K];   // 1e4 * 1e3 * 4 = 4e7 = 40 MB
int mx[MAX_N][MAX_K];

int main() {
    freopen("teamwork.in", "r", stdin);
    freopen("teamwork.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &x: a) cin >> x;
    memset(dp, 0, sizeof(dp));
    memset(mx, 0, sizeof(mx));

    for (int i = 0; i < n; i++) {
        // -= prev_mx * (k - 1) + mx * k
        for (int j = 0; j <= k && j <= i; j++) {
            int &new_group = dp[i + 1][1];
            int &new_group_mx = mx[i + 1][1];
            if (dp[i][j] + a[i] > new_group) {
                new_group = dp[i][j] + a[i];
                new_group_mx = a[i];
            }

            int &same_group = dp[i + 1][j + 1];
            int &same_group_mx = mx[i + 1][j + 1];
            int old_mx = mx[i][j];
            int new_mx = max(a[i], old_mx);
            int new_value_contribution = new_mx * (j + 1) - old_mx * j;
            if (new_value_contribution + dp[i][j] > same_group) {   // this IF is not required (I think)
                same_group = new_value_contribution + dp[i][j];
                same_group_mx = new_mx;
            }
        }
    }
    // for (int i = 0; i <= n; i++) {
    //     for (int j = 0; j <= k; j++) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    int ans = 0;
    for (int i = 0; i <= k; i++) {
        ans = max(ans, dp[n][i]);
    }
    cout << ans << '\n';
    return 0;
}
