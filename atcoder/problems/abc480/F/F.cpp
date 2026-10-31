#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int64_t> a(n);
    for (auto &ai: a) {
        cin >> ai;
        ai *= m;
    }
    int64_t total = accumulate(a.begin(), a.end(), 0LL);
    int64_t each = total / m;
    vector<int> dp(1 << n, INT_MAX);
    dp[0] = 0;
    for (int mask = 0; mask < (1 << n) - 1; mask++) {
        int64_t cur = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                cur += a[i];
            }
        }
        int64_t rem = each - (cur % each);
        if (rem == 0) rem = each;
        for (int i = 0; i < n; i++) {
            if ((mask & (1 << i)) == 0) {
                int newmask = mask | (1 << i);
                int64_t cake = a[i];
                int cost = 0;
                int64_t cur_rem = rem;
                while (cake > cur_rem) {
                    cost++;
                    cake -= cur_rem;
                    cur_rem = each;
                }

                dp[newmask] = min(dp[newmask], dp[mask] + cost);
            }
        }
    }
    cout << dp[(1 << n) - 1] << '\n';
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
