#include <bits/stdc++.h>
using namespace std;

#define sz(v) int(v.size())

const int64_t MOD = 998244353;

const int MAX = int(5e3);
int64_t pow2s[MAX + 1];
void precompute() {
    pow2s[0] = 1;
    for (int i = 1; i <= MAX; i++) {
        pow2s[i] = pow2s[i-1]*2 % MOD;
    }
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    int mx = *max_element(a.begin(), a.end());

    vector<int> l, r;
    for (int i = 0; i < n; i++) {
        if (l.empty() || l.back() < a[i]) l.push_back(a[i]);
    }
    for (int i = n - 1; i >= 0; i--) {
        if (r.empty() || r.back() < a[i]) r.push_back(a[i]);
    }

    auto go = [&](vector<int> const& arr) {
        int k = sz(arr);
        vector<vector<int64_t>> dp(n + 1, vector<int64_t>(k + 1));
        dp[0][0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < sz(arr); j++) {
                dp[i][j] += dp[i-1][j];
                if (a[i] == arr[j]) {
                    dp[i][j+1] += dp[i-1][j];
                }
                else if (j > 0) {
                    if (a[i] <= arr[j-1]) {
                        dp[i][j] += dp[i-1][j];
                    }
                }

                dp[i][j] %= MOD;
            }
            dp[i][sz(arr)] %= MOD;
        }
        return dp;
    };

    a.insert(a.begin(), 0);
    vector<vector<int64_t>> dpl = go(l);
    a.erase(a.begin());

    reverse(a.begin(), a.end());
    a.insert(a.begin(), 0);
    vector<vector<int64_t>> dpr = go(r);
    a.erase(a.begin());
    reverse(a.begin(), a.end());

    reverse(dpr.begin(), dpr.end());
    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] != mx) continue;
        for (int j = i; j < n; j++) {
            if (a[i] == mx && a[j] == mx) {
                int mid_sz = max(0, j - i - 1);
                int64_t mid_contrib = pow2s[mid_sz];

                // [idx][sz(arr-1)]: excludes the maximum element
                // i+1 and j because of the way we reverse.
                // But it doesn't matter much because choosing previous is the same as current if we're handling a max
                int64_t sides_contrib = dpl[i+1][sz(l)-1] * dpr[j][sz(r)-1] % MOD;

                ans += mid_contrib * sides_contrib % MOD;
                ans %= MOD;
            }
        }
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    precompute();
    while (t--) {
        solve();
    }
    return 0;
}
