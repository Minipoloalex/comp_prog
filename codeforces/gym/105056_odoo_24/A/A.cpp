#include <bits/stdc++.h>
using namespace std;

void solve()
{
    string s;
    cin >> s;

    const string T = "ODOO";
    int n = int(s.size()), m = 4;

    const int inf = int(1e9);
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, inf));

    dp[0][0] = 0;

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            if (j > 0)
                dp[i][j] = min(dp[i][j - 1] + 1, dp[i][j]);
            if (i > 0)
                dp[i][j] = min(dp[i - 1][j] + 1, dp[i][j]);
            if (i > 0 && j > 0 && s[i - 1] == T[j - 1])
                dp[i][j] = min(dp[i - 1][j - 1], dp[i][j]);
        }
    }

    cout << dp[n][m] << '\n';
}

int main()
{
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
