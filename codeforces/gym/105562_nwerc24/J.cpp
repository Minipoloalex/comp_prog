#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<array<int,4>> c(n);
    for (int i = 0; i < n; i++) {
        auto &[x, y, h, idx] = c[i];
        cin >> x >> y >> h;
        idx = i;
    }
    sort(c.begin(), c.end(), [](array<int, 4> &a, array<int,4> &b) {
        return a[2] > b[2];
    });
    auto dist_sq = [&](int i, int j) {
        auto &[xa, ya, ha, ida] = c[i];
        auto &[xb, yb, hb, idb] = c[j];
        int xd = xa - xb;
        int yd = ya - yb;
        return xd * xd + yd * yd;
    };
    vector<pair<int,int>> ans(n);
    for (int i = 0; i < n; i++) {
        int idx = c[i][3];
        int min_dist_sq = c[i][2] * c[i][2];
        for (int j = 0; j < i; j++) {
            min_dist_sq = min(min_dist_sq, dist_sq(i, j));
        }
        int mx_radius = int(sqrtl(min_dist_sq));
        ans[i] = make_pair(idx, mx_radius);
    }
    sort(ans.begin(), ans.end());
    for (int i = 0; i < n; i++) {
        cout << ans[i].second << '\n';
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
