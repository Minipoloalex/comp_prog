#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<pair<int,int>> a(n);
    for (auto &[x, y]: a) {
        cin >> x >> y;
    }
    vector<int> xs(n), ys(n);
    for (int i = 0; i < n; i++) {
        xs[i] = a[i].first;
        ys[i] = a[i].second;
    }
    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());
    int64_t ans = 0;
    if (n == 1) {
        cout << "1\n";
    }
    else {
        ans = INT64_MAX;
        for (int i = 0; i < n; i++) {
            auto &[xi, yi] = a[i];
            pair<int,int> x = {xs[0], xs[n - 1]}, y = {ys[0], ys[n - 1]};
            x.first = xs[0];
            if (xi == xs[0]) {
                x.first = xs[1];
            }
            if (xi == xs[n-1]) {
                x.second = xs[n - 2];
            }
            if (yi == ys[0]) {
                y.first = ys[1];
            }
            if (yi == ys[n - 1]) {
                y.second = ys[n - 2];
            }
            int64_t cur = int64_t(x.second - x.first + 1) * (y.second - y.first + 1);
            if (n - 1 == cur) {
                cur += min(int64_t(x.second - x.first + 1), int64_t(y.second - y.first + 1));
            }
            ans = min(ans, cur);
        }
        cout << ans << '\n';
    }
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
