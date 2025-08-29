#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1), b(m + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++) cin >> b[i];
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, INT_MIN));
    vector<vector<ii>> par(n + 1, vector<ii>(m + 1, {0, 0}));
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 0;
    }
    for (int j = 0; j <= m; j++) {
        dp[0][j] = 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i] == b[j]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                par[i][j] = {-1,-1};
            }
            if (dp[i][j - 1] > dp[i][j]) {
                par[i][j] = {0, -1};
                dp[i][j] = dp[i][j - 1];
            }
            if (dp[i - 1][j] > dp[i][j]) {
                par[i][j] = {-1, 0};
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    cout << dp[n][m] << '\n';
    int curi = n, curj = m;
    ii iden = {0, 0};
    vector<int> ans;
    while (par[curi][curj] != iden) {
        auto [di, dj] = par[curi][curj];
        if (di == -1 && dj == -1) {
            ans.push_back(a[curi]); // same as b[curj]
        }
        curi += di;
        curj += dj;
    }
    reverse(ans.begin(), ans.end());
    assert(int(ans.size()) == dp[n][m]);
    for (int v: ans) cout << v << " ";
    cout << '\n';
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
