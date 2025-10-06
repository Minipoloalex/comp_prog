#include <bits/stdc++.h>
using namespace std;

void solve() {
    int h, d;
    cin >> h >> d;
    auto dist_cost = [&](int dist) {
        return 1LL * dist * (dist + 1) / 2;
    };
    auto total_cost = [&](int stop_cnt) {
        int total_moves = stop_cnt + 1;
        int dist = d / total_moves;
        int rem = d % total_moves;
        return rem * dist_cost(dist + 1) + (total_moves - rem) * dist_cost(dist);
    };
    int lo = 0, hi = d;
    while (lo < hi) {
        int m = lo + (hi - lo) / 2;
        if (total_cost(m) <= h + m - 1) {
            hi = m;
        }
        else {
            lo = m + 1;
        }
    }
    cout << lo + d << '\n';
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
