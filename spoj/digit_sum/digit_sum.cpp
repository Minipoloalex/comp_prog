#include <bits/stdc++.h>
using namespace std;

uint64_t dp[16][2];
int64_t cnt[16][2];

pair<uint64_t, int64_t> go(int i, int under, vector<int> &digits) {
    if (i == int(digits.size())) {
        return {0, 1};
    }

    uint64_t &ans = dp[i][under];
    int64_t &ct = cnt[i][under];
    if (ct != -1) return {ans, ct};

    int max_digit = under ? 9 : digits[i];
    uint64_t val = 0;
    int64_t total_cnt = 0;
    for (int d = 0; d <= max_digit; d++) {
        int new_under = under ? true : d < max_digit;
        auto [sm, nxt_cnt] = go(i + 1, new_under, digits);
        total_cnt += nxt_cnt;
        val += sm + d * nxt_cnt;
    }
    ans = val;
    ct = total_cnt;
    return {ans, ct};
}

uint64_t get(int64_t x) {
    vector<int> digits;
    while (x) {
        int d = int(x % 10);
        digits.push_back(d);
        x /= 10;
    }
    reverse(digits.begin(), digits.end());
    memset(cnt, -1, sizeof(cnt));
    auto [ans, ct] = go(0, 0, digits);
    return ans;
}

void solve() {
    int64_t a, b;
    cin >> a >> b;
    int64_t ans = get(b);
    // cout << get(b) << " ";
    if (a - 1 > 0) {
        ans -= get(a - 1);
        // cout << get(a - 1) << " ";
    }
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
