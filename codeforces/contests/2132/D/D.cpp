#include <bits/stdc++.h>
using namespace std;

vector<int64_t> pows;

void precompute() {
    pows.assign(16, 1);
    for (int i = 1; i <= 15; i++) {
        pows[i] = pows[i - 1] * 10;
    }
}

vector<int64_t> get_digits(int64_t nr) {
    vector<int64_t> ans;
    while (nr) {
        int64_t d = nr % 10;
        ans.push_back(d);
        nr /= 10;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

void solve() {
    int64_t k;
    cin >> k;
    auto sum = [&](int64_t last_nr) {
        int64_t n = last_nr;
        int64_t total = 0;
        int x = 0;
        int64_t cur_lsb = 0;
        while (n) {
            int64_t d = n % 10;
            n /= 10;
            for (int64_t i = 1; i < 10; i++) {
                // how many times does this digit appear
                int64_t times = n * pows[x];
                if (i < d) {
                    times += pows[x];
                }
                if (i == d) {
                    // grab the least significant part
                    times += cur_lsb + 1;
                }
                total += times * i;
            }
            cur_lsb += d * pows[x];
            x++;
        }
        return total;
    };
    auto cnt = [&](int64_t last_nr) {
        int64_t n = last_nr;
        int x = 0;
        int64_t ans = 0;
        while (n >= 10) {
            n /= 10;
            ans += 9 * pows[x] * (x + 1);
            x++;
        }
        int64_t sub = pows[x] - 1;
        ans += (last_nr - sub) * (x + 1);
        return ans;
    };
    int64_t lo = 1, hi = int64_t(1e14);
    while (lo < hi) {
        int64_t med = (lo + hi + 1) / 2;
        if (cnt(med) < k) {
            lo = med;
        }
        else {
            hi = med - 1;
        }
    }
    auto remainder = [&](int64_t nr, int64_t remainder_cnt) {
        vector<int64_t> digits = get_digits(nr);
        int64_t additional = 0;
        for (int i = 0; i < remainder_cnt; i++) {
            additional += digits[i];
        }
        return additional;
    };
    int64_t remainder_cnt = k - cnt(lo);
    int64_t ans = sum(lo) + remainder(lo + 1, remainder_cnt);
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
