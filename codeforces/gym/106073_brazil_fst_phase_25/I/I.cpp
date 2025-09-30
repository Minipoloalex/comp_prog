#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int64_t> dist(n-1);
    int64_t x, y;
    cin >> x >> y;

    for (int i = 0; i < n - 1; i++) {
        int64_t nx, ny;
        cin >> nx >> ny;
        dist[i] = abs(x - nx) + abs(y - ny);
        x = nx; y = ny;
    }

    vector<int64_t> c(n, 0);
    for (int i = 1; i < n; i++) {
        c[i] = dist[i-1] - c[i-1];
    }

    array<int64_t, 2> bounds = { 1, int64_t(1e18) };
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            bounds[0] = max(bounds[0], -c[i] + 1);
        }
        else {
            bounds[1] = min(bounds[1], c[i] - 1);
        }
    }

    cout << (bounds[0] <= bounds[1] ? bounds[1] : -1) << '\n';
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
