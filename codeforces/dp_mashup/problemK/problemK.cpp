#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<vector<int64_t>> dp(n, vector<int64_t>(k, -1));

    const int64_t mod = int64_t(1e9 + 7);
    auto func = [&](int64_t value, int pos, auto &&self) -> int64_t {
        if (pos == k) return 1;     // finished
        if (value == n) return 1;   // would have to multiply everything by 1, only 1 way to do it

        int64_t &ans = dp[value][pos];
        if (ans != -1) return ans;

        int64_t curr = 0;
        for (int64_t next = value; next <= n; next += value) {
            curr = (curr + self(next, pos + 1, self)) % mod;
        }
        ans = curr % mod;
        return ans;
    };
    cout << func(1, 0, func) << '\n';
    return 0;
}
