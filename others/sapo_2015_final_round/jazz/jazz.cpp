#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s;
    cin >> s;
    int n = int(s.size());
    vector<vector<int>> dp(n, vector<int>(n, -1));
    function<int(int,int)> go = [&](int i, int j) {
        if (i > j) return 0;
        // if (i == j) return 1;    // actually don't need this base case here
        int &ans = dp[i][j];
        if (ans != -1) return ans;
        int cur = go(i + 1, j) + 1; // duplicated s[i]
        for (int idx = i + 1; idx <= j; idx++) {
            if (s[i] == s[idx]) {
                // handle in the middle [i + 1, idx - 1] and handle after it [idx + 1, j]
                cur = min(cur, go(i + 1, idx - 1) + go(idx + 1, j));
            }
        }
        return ans = cur;
    };
    int ans = go(0, n - 1);
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
