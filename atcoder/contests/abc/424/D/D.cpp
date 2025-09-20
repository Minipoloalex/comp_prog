#include <bits/stdc++.h>
using namespace std;

void solve() {
    int h, w;
    cin >> h >> w;
    vector<string> g(h);
    for (auto &s: g) cin >> s;
    auto all_black = [&](int i, int j) {
        return g[i][j] == '#' && g[i+1][j] == '#' && g[i][j+1] == '#' && g[i+1][j+1] == '#';
    };
    vector<vector<int>> dp(w, vector<int>(1 << h, -1));
    function<int(int,int)> go = [&](int j, int prvmask) {
        if (j == w) return 0;

        int &mem = dp[j][prvmask];
        if (mem != -1) return mem;

        int mn = INT_MAX;
        for (int mask = 0; mask < (1 << h); mask++) {   // 1 in the mask means colored white
            // check if valid
            bool valid = true;
            if (j > 0) {
                for (int i = 0; i < h - 1; i++) {
                    if (all_black(i, j-1)) {
                        if ((prvmask & (1 << i)) == 0 && (prvmask & (1 << (i+1))) == 0 && 
                        (mask & (1 << i)) == 0 && (mask & (1 << (i+1))) == 0) {
                            valid = false;
                        }
                    }
                }
            }
            if (valid) {
                mn = min(mn, __builtin_popcount(mask) + go(j + 1, mask));
            }
        }
        return mem = mn;
    };
    int ans = go(0, 0);
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
