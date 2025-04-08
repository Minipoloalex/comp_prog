#include <bits/stdc++.h>
using namespace std;

const int MAX_SUM = int(1e5);
bitset<MAX_SUM + 1> bs;

const int MAX_N = 100;
bool dp[MAX_N + 1][MAX_SUM + 1];

void solve() {
    int n;
    cin >> n;
    vector<int> x(n);
    for (auto &xi: x) cin >> xi;

    // other solution:
    // bs[0] = 1;
    // for (int i = 0; i < n; i++) {
    //     for (int s = MAX_SUM; s >= 0; s--) {
    //         if (s - x[i] >= 0 && bs[s - x[i]]) {
    //             bs[s] = 1;
    //         }
    //     }
    // }
    // cout << bs.count() - 1 << '\n';
    // for (int i = 1; i <= MAX_SUM; i++) {
    //     if (bs[i]) {
    //         cout << i << " ";
    //     }
    // }
    // cout << '\n';

    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int s = 0; s <= MAX_SUM; s++) {
            if (dp[i][s]) {
                dp[i + 1][s] = dp[i][s];
                dp[i + 1][s + x[i]] = 1;    // not a problem
            }
        }
    }
    vector<int> ans;
    for (int s = 1; s <= MAX_SUM; s++) {
        if (dp[n][s]) ans.push_back(s);
    }
    cout << ans.size() << '\n';
    for (int a: ans) cout << a << " ";
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
