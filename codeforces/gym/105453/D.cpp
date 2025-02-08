#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s;
    cin >> s;
    int n = int(s.size());

    int m;
    cin >> m;
    vector<string> ms(m);
    for (auto &mi: ms) cin >> mi;

    // recursive dp solution
    // vector<int> dp(n, -1);
    // auto go = [&](int i, auto &&self) -> int {
    //     if (i == n) return 0;

    //     int &ans = dp[i];
    //     if (ans != -1) return ans;

    //     int cur = 0;
    //     for (int j = 0; j < m; j++) {
    //         if (s.substr(i, (int) ms[j].size()) == ms[j]) {
    //             int nxt = self(i + (int) ms[j].size(), self);
    //             cur = max(cur, (int) ms[j].size() + nxt);
    //         }
    //     }
    //     self(i + 1, self);
    //     ans = max(ans, cur);
    //     return ans;
    // };
    // go(0, go);
    // int ans = 0;
    // for (int i = 0; i < n; i++) {
    //     ans = max(ans, dp[i]);
    // }

    // iterative dp solution
    vector<int> dp(n + 1, 0);
    int ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < m; j++) {
            int m_sz = int(ms[j].size());
            if (s.substr(i, m_sz) == ms[j]) {
                dp[i] = max(dp[i], m_sz + dp[i + m_sz]);
            }
        }
        ans = max(ans, dp[i]);
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
