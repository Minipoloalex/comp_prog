#include <bits/stdc++.h>
using namespace std;

typedef vector<int64_t> vi;

void solve() {
    int r, n, m;
    cin >> r >> n >> m;
    vector<vi> dp(n + 1, vi(n + 1, -1));
    function<int64_t(int,int,int,int)> go = [&](int i, int full, int ones, int zeros) -> int64_t {
        if (i == 0) return 1;

        int64_t &ans = dp[i][full];
        if (ans != -1) return ans;

        // int previously_placed = n - i;  // i: 1-indexed
        int possible_zero_choices = zeros;
        if (i < r) {
            possible_zero_choices--;
        }

        int64_t cur = ones * go(i - 1, full + 1, ones - 1, zeros + 1) % m;
        cur = cur + possible_zero_choices * go(i - 1, full, ones + 1, zeros) % m;

        return ans = cur;
    };
    int64_t ans = go(n - 1, 0, 0, 1);
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
