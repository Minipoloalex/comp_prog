#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> w(n);
    for (auto &wi: w) cin >> wi;
    vector<pair<int,int>> dp(1 << n, {-1,-1});

    // we can avoid 2^n * n^2 (i.e. avoid additional state: nrides)
    // because it's always best to use less rides (even if leads to more weight for the last ride)
    function<pair<int,int>(int)> go = [&](int mask) -> pair<int,int> {
        if (mask == 0) {
            return {0, 0};
        }
        pair<int,int> &mem = dp[mask];
        if (mem.first != -1) return mem;

        pair<int,int> best = {INT_MAX, INT_MAX};
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                pair<int,int> cur = go(mask ^ (1 << i));
                if (cur.second + w[i] <= x) {
                    cur.second += w[i];
                }
                else {
                    cur.second = w[i];
                    cur.first++;
                }
                if (cur.second == x) {
                    cur.second = 0;
                    cur.first++;
                }
                best = min(best, cur);
            }
        }
        return mem = best;
    };
    pair<int,int> ans = go((1 << n) - 1);
    cout << ans.first + (ans.second > 0) << '\n';
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
