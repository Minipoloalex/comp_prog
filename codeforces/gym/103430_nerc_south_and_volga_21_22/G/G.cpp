#include <bits/stdc++.h>
using namespace std;

void solve() {
    int64_t k, x;
    cin >> k >> x;
    auto nr_emotes = [&](int64_t med) {
        int64_t fst_limit = min(med, k);
        int64_t cnt_fst = (1 + fst_limit) * fst_limit / 2;
        int64_t cnt_snd = 0;
        if (med > k) {
            int64_t diff = med - k;
            int64_t final = k - diff;
            cnt_snd = (k - 1 + final) * diff / 2;
        }
        return cnt_fst + cnt_snd;
    };
    int64_t lo = 0, hi = 2*k-1;
    while (lo < hi) {
        int64_t med = lo + (hi - lo) / 2;
        if (nr_emotes(med) >= x) {
            hi = med;
        }
        else {
            lo = med + 1;
        }
    }
    cout << lo << '\n';
    // int64_t lo = 0, hi = 2*k-1;
    // while (lo < hi) {
    //     int64_t med = lo + (hi - lo + 1) / 2;
    //     if (nr_emotes(med) > x) {
    //         hi = med - 1;
    //     }
    //     else {
    //         lo = med;
    //     }
    // }
    // // we found the first one where it's >= x
    // // edge case here
    // if (nr_emotes(lo) < x && lo < 2*k-1) {
    //     lo++;
    // }
    // cout << lo << '\n';
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
