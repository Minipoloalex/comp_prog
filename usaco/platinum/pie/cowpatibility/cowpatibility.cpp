#include <bits/stdc++.h>
using namespace std;

#define sz(v) int(v.size())

// PIE solution
// there is also a (cool) bitset solution
void solve() {
    int n;
    cin >> n;
    vector<int> ice(5);
    map<vector<int>,int> subsets;   // will tell me how many are compatible
    for (int i = 0; i < n; i++) {
        for (auto &ic: ice) cin >> ic;
        sort(ice.begin(),ice.end());
        for (int mask = 1; mask < (1 << 5); mask++) {
            vector<int> subset;
            for (int j = 0; j < 5; j++) {
                if ((1 << j) & mask) {
                    subset.push_back(ice[j]);
                }
            }
            subsets[subset]++;
        }
    }
    int64_t ans = 1LL * n * (n - 1) / 2;    // all pairs
    for (auto &[subset, freq]: subsets) {
        int64_t pairs = 1LL * freq * (freq - 1) / 2;
        if (sz(subset) % 2 == 0) {
            ans += pairs;
        }
        else {
            ans -= pairs;   // e.g. size = 1: subtract compatible pairs
        }
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    freopen("cowpatibility.in", "r", stdin);
    freopen("cowpatibility.out", "w", stdout);
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
