#include <bits/stdc++.h>
using namespace std;

int64_t dp[1010][2010];

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n, k, p;
    cin >> n >> k >> p;
    vector<int> a(n), b(k);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < k; i++) cin >> b[i];
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    memset(dp, -1, sizeof dp);

    auto func = [&](int pi, int ki, auto &&self) -> int64_t {
        if (pi == n) return 0;          // no more people
        if (ki == k) return INT64_MAX;  // no more keys, but still more people to assign to (cannot be a solution)

        int64_t &ans = dp[pi][ki];
        if (ans != -1) return ans;

        int64_t curr = INT64_MAX;
        for (int i = ki; i < k && n - pi <= k - i; i++) {
            // assign person pi to key i
            int64_t time_taken = abs(a[pi] - b[i]) + abs(b[i] - p);
            dp[pi][i] = max(time_taken, self(pi + 1, i + 1, self));
            curr = min(curr, dp[pi][i]);
        }
        ans = curr;
        return ans;
    };
    cout << func(0, 0, func) << '\n';
    return 0;
}
