#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

int dp[32][91][91][2];    // 1e5 * 1e5 * 2 * 32 = 64 * 1e10 = 1e12 = 1 TB
vi digits;

int a, b, k;

int call_dp(int pos, int cnt, int flag, int curr_number_mod) {
    if (pos == (int) digits.size()) {
        if (cnt % k == 0 && curr_number_mod % k == 0) {
            return 1;
        }
        return 0;
    }
    if (dp[pos][cnt][curr_number_mod][flag] != -1) {
        return dp[pos][cnt][curr_number_mod][flag];
    }

    int limit = flag == 0 ? digits[pos] : 9;

    int value = 0;
    for (int digit = 0; digit <= limit; digit++) {
        int nflag = flag == 1 ? flag : (digit < limit);
        int val = call_dp(pos + 1, (cnt + digit) % k, nflag, (curr_number_mod * 10 + digit) % k);
        value += val;
    }
    return dp[pos][cnt][curr_number_mod][flag] = value;
}

int solve(int num) {
    digits.clear();
    while (num != 0) {
        digits.push_back(num % 10);
        num /= 10;
    }
    reverse(digits.begin(), digits.end());
    memset(dp, -1, sizeof(dp));
    return call_dp(0, 0, 0, 0);
}


int main() {
    int t;
    cin >> t;
    for (int c = 1; c <= t; c++) {
        cin >> a >> b >> k;
        int result;
        if (k >= 90) {
            result = 0;
        }
        else {
            int bval = solve(b);
            int aval = solve(a - 1);
            result = bval - aval;
        }
        cout << "Case " << c << ": " << result << '\n';
    }
    return 0;
}
