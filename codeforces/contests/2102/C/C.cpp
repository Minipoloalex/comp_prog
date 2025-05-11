#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    int cur_nr = n * n - 1;
    vector<vector<int>> g(n, vector<int>(n, 0));
    int cur = n;
    int s = 0, e = n - 1;
    while (cur_nr >= 0) {
        g[s][s] = cur_nr--;
        for (int r = s + 1; r <= e; r++) {
            g[r][s] = cur_nr--;
        }
        for (int c = s + 1; c <= e; c++) {
            g[s][c] = cur_nr--;
        }
        cur--;
        s++;
        if (cur == 0) break;

        g[e][e] = cur_nr--;
        for (int r = s; r < e; r++) {
            g[r][e] = cur_nr--;
        }
        for (int c = s; c < e; c++) {
            g[e][c] = cur_nr--;
        }
        cur--;
        e--;
    }
    for (auto &r: g) {
        for (auto &v: r) {
            cout << v << " ";
        }
        cout << '\n';
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
