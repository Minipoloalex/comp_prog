#include <bits/stdc++.h>
using namespace std;

void solve() {
    int h, w, xa, ya, xb, yb;
    cin >> h >> w >> xa >> ya >> xb >> yb;
    if (xa > xb) {
        cout << "Draw\n";
        return;
    }
    int dx = xb - xa;
    int ya_min, ya_max, yb_min, yb_max;
    int moves_a = (dx + 1) / 2;
    int moves_b = dx / 2;
    ya_min = max(ya - moves_a, 1);
    ya_max = min(ya + moves_a, w);
    yb_min = max(yb - moves_b, 1);
    yb_max = min(yb + moves_b, w);
    string ans = "Draw";
    auto inside = [&](int y1, int y2, int ymin, int ymax) {
        // y1 <= y2
        // ymin <= ymax;
        return ymin <= y1 && y2 <= ymax;
    };
    if (dx % 2 == 0) {
        // even, so Bob may win
        // alice wants to run
        if (inside(ya_min, ya_max, yb_min, yb_max)) {
            ans = "Bob";
        }
    }
    else {
        if (inside(yb_min, yb_max, ya_min, ya_max)) {
            ans = "Alice";
        }
    }
    cout << ans << '\n';
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
