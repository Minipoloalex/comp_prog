#include <bits/stdc++.h>
using namespace std;

vector<int64_t> pows;

void precompute() {
    pows.assign(21, 1);
    for (int i = 1; i <= 20; i++) {
        pows[i] = pows[i - 1] * 3;
    }
}

int64_t cost(int64_t x) {
    if (x == 0) {
        return 3;    
    }
    return pows[x + 1] + x * pows[x - 1];
}

void solve() {
    int n, k;
    cin >> n >> k;

    int bit = 0;
    int64_t ans = 0;
    int min_deals = 0;
    int nn = n;
    vector<int> digits;
    while (nn) {
        int digit = nn % 3;
        ans += digit * cost(bit++);
        nn /= 3;

        digits.push_back(digit);
        min_deals += digit;
    }

    if (min_deals > k) {
        cout << "-1\n";
        return;
    }
    else {
        int rem = k - min_deals;
        for (int x = int(digits.size()) - 1; x >= 1; x--) { // start from MSB
            int d = digits[x];
            int mx_additional = min(d * 2, rem);
            if (mx_additional <= 1) {
                break;
            }
            int to_move = mx_additional / 2;
            ans -= 1LL * to_move * cost(x);
            ans += 3LL * to_move * cost(x - 1);

            digits[x - 1] += 3 * to_move;
            rem -= 2 * to_move;
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
