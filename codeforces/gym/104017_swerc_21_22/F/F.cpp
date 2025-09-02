#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    array<int, 2> maxes = {0, 0};

    for (int i = 0; i < m; i++) {
        int r, w;
        cin >> r >> w;

        maxes[0] = max(maxes[0], r);
        maxes[1] = max(maxes[1], w);
    }

    auto [r, w] = maxes;
    if (r + w > n) {
        cout << "IMPOSSIBLE\n";
        return;
    }

    for (int i = 0; i < r; i++) cout << 'R';
    for (int i = 0; i < w; i++) cout << 'W';
    for (int i = r + w; i < n; i++) cout << 'R';
    cout << '\n';
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
