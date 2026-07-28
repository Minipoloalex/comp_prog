#include <bits/stdc++.h>
using namespace std;

void solve() {
    int64_t x, y;
    cin >> x >> y;
    int64_t b = -1;
    for (int i = 29; i >= 0; i--) {
        if ((x & y) >> i) {
            b = i;
            break;            
        }
    }
    int64_t mn = INT64_MAX;
    int64_t ansp, ansq;
    auto update_ans = [&](int64_t p, int64_t q) {
        if (p & q) return;
        int64_t cost = abs(p-x) + abs(q-y);
        if (cost < mn) {
            ansp = p;
            ansq = q;
            mn = cost;
        }
    };
    update_ans(x, y);
    if (b != -1) {
        update_ans(((x >> b) << b) + (1 << b), y);
        update_ans(x, ((y >> b) << b) + (1 << b));
        update_ans((x >> b) << b, ((y >> b) << b) - 1);
        update_ans(((x >> b) << b) - 1, (y >> b) << b);
    }
    cout << ansp << " " << ansq << '\n';
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
