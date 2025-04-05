#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 100;
const int MAX_X = int(1e6);

const int MOD = int(1e9) + 7;

void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> c(n);
    for (auto &ci: c) cin >> ci;

    vector<int64_t> dp(x + 1, 0);
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        for (int xi = 0; xi <= x; xi++) {
            if (xi + c[i] <= x) {
                (dp[xi + c[i]] += dp[xi]) %= MOD;
            }
        }
    }
    cout << dp[x] << '\n';
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
