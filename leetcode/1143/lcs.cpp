#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        string &s = text1;
        string &t = text2;
        int n = int(s.size());
        int m = int(t.size());
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                if (s[i] == t[j] && i + 1 <= n && j + 1 <= m) {
                    dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] + 1);
                }
                if (i + 1 <= n) {
                    dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
                }
                if (j + 1 <= m) {
                    dp[i][j + 1] = max(dp[i][j + 1], dp[i][j]);
                }
            }
        }
        return dp[n][m];
    }
};


int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    string s, t;
    cin >> s >> t;
    Solution sol;
    int ans = sol.longestCommonSubsequence(s, t);
    cout << ans << '\n';
    return 0;
}
