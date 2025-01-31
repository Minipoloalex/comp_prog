#include <bits/stdc++.h>
using namespace std;

int main() {
    int tt;
    cin >> tt;
    while (tt--) {
        int n, m;
        cin >> n >> m;

        vector<vector<int>> el(n, vector<int>());
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--; v--;
            el[u].push_back(v);
        }

        vector<int> dp(n, INT_MAX);
        dp[0] = 0;
        for (int i = 0; i < n; i++) {
            vector<int> &edges = el[i];
            for (int v: edges) {
                dp[v] = min(dp[v], dp[i] + 1);
            }
            if (i + 1 < n) {
                dp[i + 1] = min(dp[i + 1], dp[i] + 1);
            }
            // cout << dp[i] << " ";
        }
        // cout << endl;

        vector<int> res(n, 0);
        for (int i = 0; i < n; i++) {
            vector<int> &edges = el[i];
            int t = dp[i];
            for (int v: edges) {
                int l = i + 1;      // inclusive (in-bounds since v > i)
                int r = v - t - 1;  // exclusive (in-bounds since v >= i + 1, t <= i)
                if (r > l) {
                    res[l]++;
                    res[r]--;
                }
            }
        }
        for (int i = 1; i < n; i++) {
            res[i] += res[i - 1];
        }
        for (int i = 0; i < n - 1; i++) {
            if (res[i] > 0) {   // elsie wins
                cout << "0";    // bessie loses
            }
            else cout << "1";
        }
        cout << '\n';
    }
    return 0;
}
