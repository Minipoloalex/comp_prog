#include <bits/stdc++.h>
using namespace std;

pair<int64_t,int64_t> norm(int64_t a, int64_t b) {
    int64_t g = gcd(a, b);
    return {a / g, b / g};
}

void solve() {
    int64_t c, d;
    string a, b;
    cin >> a >> b >> c >> d;

    tie(c, d) = norm(c, d);
    int dsize = int(to_string(d).size());

    int sz = int(a.size());
    for (int m = 1; m < (1 << sz); m++) {
        vector<int> to_remove(10);
        bool valid = true;
        int64_t A = 0;
        for (int i = 0; i < sz; i++) {
            int digit = a[i] - '0';
            if (m & (1 << i)) {
                if (digit == 0 && A == 0) {
                    valid = false;
                }
                A *= 10;
                A += digit;
            }
            else {
                to_remove[digit]++;
            }
        }
        if (valid) {
            if (A >= c && A % c == 0) {
                // This method works for checking overflow
                int64_t mult = A / c;
                int sz_mult = int(to_string(mult).size()) + dsize - 1;
                if (sz_mult >= 19) continue;
                uint64_t B = d * mult;

                // Could have also used int128 to check it
                // __int128 B128 = (__int128)d * (__int128)mult;
                // if (B128 > __int128_t(1e18)) continue;
                // int64_t B = int64_t(B128);

                string to_check_B = to_string(B);
                int l = 0;
                for (int i = 0; i < int(to_check_B.size()) && valid; i++, l++) {
                    if (l == int(b.size())) {
                        valid = false;
                        break;
                    }
                    while (b[l] != to_check_B[i]) {
                        int orig_digit = b[l] - '0';
                        if (to_remove[orig_digit] == 0) {
                            valid = false;
                            break;
                        }
                        to_remove[orig_digit]--;
                        l++;
                    }
                }
                while (l < int(b.size())) {
                    int orig_digit = b[l] - '0';
                    if (to_remove[orig_digit] == 0) valid = false;
                    to_remove[orig_digit]--;
                    l++;
                }
                if (accumulate(to_remove.begin(), to_remove.end(), 0) > 0) {
                    valid = false;
                }
                if (valid) {
                    cout << "possible\n";
                    cout << A << " " << B << '\n';
                    return;
                }
            }
        }
    }
    cout << "impossible\n";
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
