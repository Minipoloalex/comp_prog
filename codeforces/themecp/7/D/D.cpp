#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m, k, d;
    cin >> n >> m >> k >> d;
    vector<vector<int>> depth(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> depth[i][j];
            depth[i][j]++;
        }
    }
    vector<int64_t> costs(n);
    for (int i = 0; i < n; i++) {
        vector<int> &row = depth[i];
        vector<int64_t> dp(m, row[0]);
        multiset<int64_t> cur = {row[0]};
        for (int j = 1; j < m; j++) {
            dp[j] = *cur.begin() + row[j];
            if (int(cur.size()) > d) {
                auto it = cur.find(dp[j - d - 1]);
                assert(it != cur.end());
                cur.erase(it);
            }
            cur.insert(dp[j]);
        }
        costs[i] = dp[m - 1];
    }
    // for (int64_t c: costs) {
    //     cout << c << " ";
    // }
    // cout << endl;
    int l = 0, r = 0;
    int64_t mn = INT64_MAX, cur = 0;
    while (r < n) {
        cur += costs[r];
        while (r - l + 1 > k) {
            cur -= costs[l];
            l++;
        }
        if (r - l + 1 == k) {
            mn = min(mn, cur);
        }
        r++;
    }
    cout << mn << '\n';
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
