#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> freq(n + 1);
    for (int i = 0; i < n; i++) {
        int ai;
        cin >> ai;
        freq[ai]++;
    }
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
    function<int(int,int)> go = [&](int cur, int turns) {
        if (cur == n + 1) return 0;

        int &ans = dp[cur][turns];
        if (ans != -1) return ans;

        int f = freq[cur];
        int curans = INT_MAX;
        if (turns >= f) {
            // A does not eat
            // B eats all "cur"
            curans = min(curans, go(cur + 1, turns - f));
        }
        // A eats, B gains one turn
        curans = min(curans, 1 + go(cur + 1, turns + 1));
        return ans = curans;
    };
    // since we do min, it ensures that A won't eat more than she should
    // (e.g. do more possible turns: n = 6 and A turns = 4)
    int ans = go(1, 0);
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
