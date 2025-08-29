#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    array<int64_t,4> vs = {INT64_MIN, INT64_MIN, INT64_MAX, INT64_MAX};
    auto insert = [&](int64_t x, int64_t y) {
        vs[0] = max(vs[0], x + y);
        vs[1] = max(vs[1], y - x);
        vs[2] = min(vs[2], x + y);
        vs[3] = min(vs[3], y - x);
    };
    auto get = [&]() {
        return max(vs[0] - vs[2], vs[1] - vs[3]);
    };
    for (int i = 0; i < n; i++) {
        int64_t x, y;
        cin >> x >> y;
        insert(x, y);
        cout << get() << '\n';
    }
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
