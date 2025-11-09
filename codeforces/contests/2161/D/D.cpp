#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    vector<vector<pair<int,int>>> occ(n);
    for (int i = 0; i < n; i++) {
        occ[a[i]-1].emplace_back(i,-1);
    }
    {
        int id = 0;
        for (int i = 0; i < n; i++) {
            for (int j = int(occ[i].size()) - 1; j >= 0; j--) {
                occ[i][j].second = id++;
            }
        }
    }
    int mx2 = 0;
    vector<int> dp(n), mx(n);
    for (int i = 0; i < n; i++) {
        if (i - 2 >= 0) {
            mx2 = max(mx2, mx[i-2]);
        }
        int mx1 = 0;
        int r = i > 0 ? int(occ[i-1].size())-1 : -1;
        for (int j = int(occ[i].size())-1; j >= 0; j--) {
            auto &[idx, id] = occ[i][j];
            if (i > 0) {
                while (r >= 0 && occ[i-1][r].first > idx) {
                    mx1 = max(mx1, dp[occ[i-1][r].second]);
                    r--;
                }
            }
            dp[id] = max({mx2, mx[i], mx1})+1;
            mx[i] = max(mx[i], dp[id]);
        }
    }
    int ans = n - *max_element(dp.begin(), dp.end());
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
