#include <bits/stdc++.h>
using namespace std;

// problem about cliques

const int MAX_N = 18;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> g(n);    // more efficient: like using bitsets
    // vector<vector<bool>> g(n, vector<bool>(n, false));   // does not TLE
    while (m--) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        g[a] |= 1 << b;
        g[b] |= 1 << a;
    }
    for (int i = 0; i < n; i++) {   // facilitates next fc check (with bitset)
        g[i] |= 1 << i;
    }
    vector<bool> fc(1 << n, true);
    for (int s = 1; s < (1 << n); s++) {
        bool res = true;
        for (int i = 0; i < n && res; i++) {
            if (!(s & (1 << i))) continue;
            if ((s & g[i]) != s) {
                res = false;
            }
            // does not TLE (N^2 * 2^N)
            // for (int j = i + 1; j < n && res; j++) {
            //     if (!(s & (1 << j))) continue;
            //     if (!g[i][j]) {
            //         res = false;
            //     }
            // }
        }
        fc[s] = res;
    }
    // for (int i = 0; i < (1 << n); i++) {
    //     cout << fc[i] << " ";
    // }
    // cout << endl;

    vector<int> dp(1 << n, INT_MAX);
    dp[0] = 0;
    int mask_sz = (1 << n) - 1;
    for (int s = 0; s < (1 << n); s++) {    // 3^N (includes inner loop)
        if (dp[s] == INT_MAX) continue;
        int rst = (~s) & mask_sz;
        // cout << s << " " << rst << ": ";
        for (int sub = rst; sub != 0; sub = (sub - 1) & rst) {
            int subset = rst ^ sub; // go through strict submasks of rst
            if (subset == 0) {
                // skip 0
                // and we want to include the complete one, so we can just do it here   
                subset = rst;
            }
            // cout << subset << " ";
            if (fc[subset]) {
                dp[s | subset] = min(dp[s | subset], dp[s] + 1);
            }
        }
        // cout << endl;
    }
    // for (int i = 0; i < (1 << n); i++) {
    //     cout << dp[i] << " ";
    // }
    // cout << endl;
    cout << dp[(1 << n) - 1] << '\n';
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
