#include <bits/stdc++.h>
using namespace std;

// good editorial: https://codeforces.com/blog/entry/5921 (contains iterative solution)
// iterative solution: based on (start, length) and iterates first on length, then on start

void solve() {
    string s;
    cin >> s;
    int n = int(s.size());
    vector<vector<int>> dp(n, vector<int>(n, -1));
    function<int(int, int)> go = [&](int i, int j) {
        if (i > j) return 1;
        int &ans = dp[i][j];
        if (ans != -1) return ans;
        int cur = 0;
        if (s[i] == s[j]) {
            cur = go(i + 1, j - 1);
        }
        return ans = cur;
    };
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            go(i,j);
        }
    }
    // now pref sums
    vector<vector<int>> pref(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int v = dp[i-1][j-1];
            pref[i][j] = pref[i-1][j] + pref[i][j-1] - pref[i-1][j-1];
            if (v != -1) {
                pref[i][j] += v;    
            }
        }
    }
    int q;
    cin >> q;
    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << pref[b][b] - pref[b][a-1] - pref[a-1][b] + pref[a-1][a-1] << '\n';
    }
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
