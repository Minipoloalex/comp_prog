#include <bits/stdc++.h>
using namespace std;

const int LOG = 20;

void solve() {
    int n;
    cin >> n;
    vector<int> x(n);
    for (auto &xi: x) cin >> xi;
    vector<array<int,2>> ans(1<<LOG);
    for (int i = 0; i < n; i++) {
        ans[x[i]][0]++;
        ans[x[i]][1]++;
    }
    for (int i = 0; i < LOG; i++) {
        for (int mask = 0; mask < (1 << LOG); mask++) {
            if (mask & (1 << i)) {
                ans[mask][0] += ans[mask ^ (1 << i)][0];    // subsets
                ans[mask ^ (1 << i)][1] += ans[mask][1];    // supersets
            }
        }
    }

    int full_mask = (1 << LOG) - 1;
    for (int i = 0; i < n; i++) {
        auto &[c1, c2] = ans[x[i]];
        int inv = ~x[i] & full_mask;
        int c3 = n - ans[inv][0]; // n minus how many are submasks of the inverse (the disjoint numbers)
        cout << c1 << " " << c2 << " " << c3 << '\n';
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
