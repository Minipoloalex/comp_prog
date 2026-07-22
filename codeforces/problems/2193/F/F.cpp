#include <bits/stdc++.h>
using namespace std;

const int UP = 1;
const int DOWN = 0;

void solve() {
    int n, ax, ay, bx, by;
    cin >> n >> ax >> ay >> bx >> by;
    vector<pair<int,int>> pts(n+2);
    vector<int> xs(n+2);
    for (int i = 0; i < n; i++) {
        cin >> xs[i];
        pts[i].first = xs[i];
    }
    xs[n] = ax;
    pts[n] = {ax, ay};
    xs[n+1] = bx;
    pts[n+1] = {bx, by};

    for (int i = 0; i < n; i++) cin >> pts[i].second;
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());

    auto get_id = [&](int x) {
        return int(lower_bound(xs.begin(), xs.end(), x) - xs.begin());
    };

    vector<pair<int,int>> ys(xs.size(), {INT_MAX, INT_MIN});
    for (auto &[xi, yi]: pts) {
        int id = get_id(xi);
        ys[id].first = min(ys[id].first, yi);
        ys[id].second = max(ys[id].second, yi);
    }

    vector<vector<int64_t>> dp(xs.size(), vector<int64_t>(2, 0));
    for (int i = 1; i < int(xs.size()); i++) {
        auto &[bmny, bmxy] = ys[i-1];
        auto &[mny, mxy] = ys[i];
        dp[i][DOWN] = min(dp[i-1][DOWN] + abs(mxy - bmny) + mxy - mny, 
            dp[i-1][UP] + abs(mxy - bmxy) + mxy - mny);
        dp[i][UP] = min(dp[i-1][UP] + abs(bmxy - mny) + mxy - mny,
        dp[i-1][DOWN] + abs(bmny - mny) + mxy - mny);
    }
    int64_t ans = dp[xs.size()-1][DOWN];    // same as UP for last x
    cout << ans + bx - ax << '\n';
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
