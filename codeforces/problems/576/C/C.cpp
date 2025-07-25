#include <bits/stdc++.h>
using namespace std;

void solve() {
    // check editorial for bounds on total distance (intuition based on Mo's order from Mo's Algorithm)
    int n;
    cin >> n;
    using T = array<int,3>;
    vector<T> pts(n);
    for (int i = 0; i < n; i++) {
        auto &[x, y, idx] = pts[i];
        cin >> x >> y;
        idx = i + 1;
    }
    int block_size = int(1e3);
    sort(pts.begin(), pts.end(), [&](const T &p1, const T &p2) {
        auto &[x1, y1, _1] = p1;
        auto &[x2, y2, _2] = p2;
        int b1 = x1 / block_size;
        int b2 = x2 / block_size;
        if (b1 < b2) return true;
        if (b1 == b2) {
            if (b1 % 2 == 0) {
                return y1 < y2;
            }
            return y1 > y2;
        }
        return false;
    });
    for (auto &[_, __, idx]: pts) {
        cout << idx << " ";
    }
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
