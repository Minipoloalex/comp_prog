#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    using T = array<int64_t,3>;
    vector<T> pts(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        pts[i] = T{x, y, i + 1};
    }
    vector<T> orig = pts;
    sort(pts.begin(), pts.end(), [&](T &a, T &b) {
        return a[0] < b[0] || (a[0] == b[0] && a[1] < b[1]);
    });

    vector<T> before_mid_x, after_mid_x;
    for (int i = 0; i < n; i++) {
        swap(pts[i][0], pts[i][1]);
    }
    for (int i = 0; i < n / 2; i++) {
        before_mid_x.push_back(pts[i]);
        after_mid_x.push_back(pts[i + n / 2]);
    }
    sort(before_mid_x.begin(), before_mid_x.end(), [&](T &a, T &b) {
        return a[0] < b[0] || (a[0] == b[0] && a[1] < b[1]);
    });
    sort(after_mid_x.begin(), after_mid_x.end(), [&](T &a, T &b) {
        return a[0] < b[0] || (a[0] == b[0] && a[1] < b[1]);
    });
    vector<pair<int,int>> ans;
    for (int i = 0; i < n / 2; i++) {
        int otheri = n / 2 - 1 - i;
        ans.emplace_back(before_mid_x[i][2], after_mid_x[otheri][2]);
    }
    // auto value = [&]() {
    //     int64_t sm = 0;
    //     for (int i = 0; i < n / 2; i++) {
    //         auto [i1, i2] = ans[i];
    //         i1--;
    //         i2--;
    //         // sm += abs(pts[i][0] - pts[n - 1 - i][0]) + abs(pts[i][1] - pts[n - 1 - i][1]);
    //         // sm += abs(pts[i][0] - pts[i + n / 2][0]) + abs(pts[i][1] - pts[i + n / 2][1]);
    //         sm += abs(orig[i1][0] - orig[i2][0]) + abs(orig[i1][1] - orig[i2][1]);
    //     }
    //     return sm;
    // };
    // cout << value() << endl;
    for (auto &[i1, i2]: ans) {
        cout << i1 << " " << i2 << '\n';
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
