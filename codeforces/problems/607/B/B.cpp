#include <bits/stdc++.h>
using namespace std;


const int MAX_N = 500;

// int dp[MAX_N][MAX_N][2];
int dp[MAX_N][MAX_N];

void solve() {
    int n;
    cin >> n;
    vector<int> c(n);
    for (auto &ci: c) cin >> ci;
    memset(dp, -1, sizeof(dp));

    // function<int(int,int,bool)> go = [&](int i, int j, bool during) -> int {
    //     if (i > j) {
    //         return 0;
    //     }
    //     int &ans = dp[i][j][during];
    //     if (ans != -1) return ans;
    //     int cur = go(i + 1, j, false) + 1; // if we eat the letter
    //     for (int idx = i; idx <= j; idx++) {
    //         if (c[i] == c[idx]) {
    //             // handle in the middle and after
    //             int v = go(i + 1, idx - 1, true) + go(idx + 1, j, false);
    //             if (!during) {
    //                 v++;    // if during, we don't need to account for the matching of c[i] == c[idx]
    //             }
    //             cur = min(cur, v);
    //         }
    //     }
    //     return ans = cur;
    // };
    function<int(int,int)> go = [&](int i, int j) -> int {
        if (i > j) {
            return 0;
        }
        int &ans = dp[i][j];
        if (ans != -1) return ans;

        // int cur = go(i + 1, j) + 1; // if we eat the letter (not necessary because idx == i leads to v++)
        int cur = INT_MAX;
        for (int idx = i; idx <= j; idx++) {
            if (c[i] == c[idx]) {
                // handle in the middle and after
                // if it has stuff in the middle, we don't count the +1 (it will be counted later)
                int v = go(i + 1, idx - 1) + go(idx + 1, j);
                if (idx <= i + 1) {
                    v++;
                }
                cur = min(cur, v);
            }
        }
        return ans = cur;
    };
    int ans = go(0, n - 1);
    cout << ans << '\n';
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
