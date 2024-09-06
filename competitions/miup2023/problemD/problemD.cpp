#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
vi digits;
ll a, b;

ll dp[65][130][2][2];

// typedef vector<ll> vl;
// typedef vector<vl> vvl;
// typedef vector<vvl> vvvl;
// typedef vector<vvvl> vvvvl;

// vvvvl _dp;

ll call_dp(int pos, int diff, int has_one, int small) {
    if (pos == (int) digits.size()) {
        if (diff > 0) {
            return 1;
        }
        return 0;
    }

    // ll &ans = _dp.at(pos).at(diff + 64).at(has_one).at(small);
    ll &ans = dp[pos][diff + 64][has_one][small];
    if (ans != -1) {
        return ans;
    }

    int limit = small == 1 ? 1 : digits[pos];

    ll result = 0;
    for (int digit = 0; digit <= limit; digit++) {
        int nsmall = small == 1 ? 1 : digit < limit;
        int ndiff = diff;
        int nhas_one = has_one;

        if (has_one && digit == 0) {
            ndiff = diff - 1;
        }
        if (digit == 1) {
            ndiff = diff + 1;
            nhas_one = 1;
        }

        ll value = call_dp(pos + 1, ndiff, nhas_one, nsmall);
        result += value;
    }
    return ans = result;
}

ll solve(ll num) {
    digits.clear();
    while (num != 0) {
        digits.push_back(num & 1);
        num /= 2;
    }
    reverse(digits.begin(), digits.end());
    // _dp.assign(65, vvvl(130, vvl(2, vl(2, -1))));
    memset(dp, -1, sizeof(dp));
    return call_dp(0, 0, 0, 0);
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> a >> b;
        ll ares = solve(a - 1);
        ll bres = solve(b);
        cout << bres - ares << '\n';
    }
    return 0;
}
