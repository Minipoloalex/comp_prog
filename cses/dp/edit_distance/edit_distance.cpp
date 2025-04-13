#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s, t;
    cin >> s >> t;
    int n = int(s.size());
    int m = int(t.size());
    vector<vector<int>> dp(n, vector<int>(m, -1));
    function<int(int, int)> go = [&](int i, int j) {
        if (i == n) return m - j;
        if (j == m) return n - i;

        int &ans = dp[i][j];
        if (ans != -1) return ans;

        dp[i][j] = min({
            1 + go(i + 1, j),
            1 + go(i, j + 1),
            (s[i] == t[j] ? 0 : 1) + go(i + 1, j + 1) 
        });
        return dp[i][j];
    };
    int ans = go(0, 0);
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
