#include <bits/stdc++.h>
using namespace std;

const int INF = int(1e9);   // values are all <= 250000

void solve_rec(int a, int b) {
    int n = max(a, b);
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
    function<int(int,int)> go = [&](int l, int r) -> int {
        if (l == r) return 0;

        int &mem = dp[l][r];
        if (mem != -1) return mem;

        int mn = INF;
        for (int m = 1; m < l; m++) {
            mn = min(mn, 1 + go(m,r) + go(l-m,r));
        }
        for (int m = 1; m < r; m++) {
            mn = min(mn, 1 + go(l,m) + go(l,r-m));
        }
        return mem = mn;
    };
    int ans = go(a, b);
    cout << ans << '\n';
}

void solve_iterative(int a, int b) {
    int n = max(a, b);
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, INF));
    for (int i = 0; i <= n; i++) {
        dp[i][i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int m = 1; m < j; m++) {
                dp[i][j] = min(dp[i][j], 1 + dp[i][m] + dp[i][j-m]);
            }
            for (int m = 1; m < i; m++) {
                dp[i][j] = min(dp[i][j], 1 + dp[m][j] + dp[i-m][j]);
            }
        }
    }
    int ans = dp[a][b];
    cout << ans << '\n';
}

void solve() {
    int a, b;
    cin >> a >> b;
    // solve_rec(a, b);
    solve_iterative(a, b);
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
