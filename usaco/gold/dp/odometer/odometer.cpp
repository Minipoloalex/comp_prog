#include <bits/stdc++.h>
using namespace std;

// problem about digit dp

int64_t dp[19][40][2][2];

int64_t go(int i, int cnt, int under, int started, vector<int> &digits, int t1, int t2) {
    // cout << i << " " << cnt << " " << under << " " << started << " " << t1 << " " << t2 << endl;
    if (i == int(digits.size())) {
        if (t2 != -1) return cnt == 0;
        return cnt >= 0;
    }
    int cnt_idx = cnt + 19;

    int64_t &ans = dp[i][cnt_idx][under][started];
    if (ans != -1) return ans;

    int max_digit = under ? 9 : digits[i];
    int64_t acc = 0;
    for (int d = 0; d <= max_digit; d++) {
        int new_under = under ? true : d < max_digit;
        int new_started = started ? true : d > 0;

        int new_cnt = cnt;
        if (new_started) {
            if (d == t1) {
                new_cnt++;
            }
            else if (d == t2) {
                new_cnt--;
            }
            else if (t2 != -1) {
                // digit is not t1 and not t2, and t2 is valid
                // so: do not need to consider this digit
                continue;
            }
            else {  // not t1, t2 not assigned
                new_cnt--;
            }
        }

        acc += go(i + 1, new_cnt, new_under, new_started, digits, t1, t2);
    }
    ans = acc;
    return ans;
};

void reset_dp() {
    memset(dp, -1, sizeof(dp));
}

int64_t get(int64_t v) {
    vector<int> digits;
    while (v) {
        int d = int(v % 10);
        digits.push_back(d);
        v /= 10;
    }
    reverse(digits.begin(), digits.end());

    int64_t ans = 0;
    for (int i = 0; i <= 9; i++) {
        reset_dp();
        ans += go(0, 0, 0, 0, digits, i, -1);
    }
    for (int i = 0; i <= 9; i++) {
        for (int j = i + 1; j <= 9; j++) {
            reset_dp();
            ans -= go(0, 0, 0, 0, digits, i, j);
        }
    }
    return ans;
}

void solve() {
    int64_t x, y;
    cin >> x >> y;
    int64_t ans = get(y) - get(x - 1);
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    freopen("odometer.in", "r", stdin);
    freopen("odometer.out", "w", stdout);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
