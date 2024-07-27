#include <bits/stdc++.h>
using namespace std;

/// @brief (pos, prev_digit, is_rising, is_lower)
int64_t dp[25][10][2][2];   // 25 * 10 * 4 = 25 * 40 = 1e3; 1e3 * 10 = 1e4
vector<int> digits;

int64_t solve_dp(int pos, int prev_digit, bool is_rising, bool is_lower) {
    if (pos == (int) digits.size()) {
        return 1;
    }

    int64_t &ans = dp[pos][prev_digit][is_rising][is_lower];
    if (ans != -1) return ans;

    int64_t curr = 0;
    int max_digit = is_lower ? 9 : digits[pos];

    if (!is_rising) max_digit = min(max_digit, prev_digit);

    for (int d = 0; d <= max_digit; d++) {
        bool new_is_lower = is_lower || d < max_digit;

        bool new_is_rising = is_rising; // if not rising, continues not rising
        if (is_rising) {
            if (d < prev_digit) {
                new_is_rising = false;
            }
        }

        curr += solve_dp(pos + 1, d, new_is_rising, new_is_lower);
    }
    ans = curr;
    return ans;
}

bool is_hill_number() {
    bool is_rising = true;
    for (int i = 1; i < (int) digits.size(); i++) {
        int prev_digit = digits[i - 1];
        int d = digits[i];

        if (d > prev_digit && !is_rising) {
            return false;
        }
        else if (is_rising && d < prev_digit) {
            is_rising = false;
        }
    }
    return true;
}

int main() {
    int64_t n;
    cin >> n;
    while (n != 0) {
        // (int) n % 10 would save n in 32 bits, only after do the % 10 -> WA
        // should probably test with numbers that require 64 bits before submitting
        digits.push_back((int) (n % 10));
        n /= 10;
    }
    reverse(digits.begin(), digits.end());

    if (!is_hill_number()) {
        cout << -1 << '\n';
        return 0;
    }

    memset(dp, -1, sizeof(dp));
    int64_t ans = solve_dp(0, 0, true, false) - 1;  // exclude 0
    cout << ans << '\n';
    return 0;
}
