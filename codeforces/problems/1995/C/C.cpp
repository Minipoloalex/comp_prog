#include <bits/stdc++.h>
using namespace std;

const int64_t inf = int(1e9);

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;

    int exp_cnt = 0;
    int64_t ans = 0;
    for (int i = 1; i < n; i++) {
        int64_t prev = a[i - 1];
        int64_t cur = a[i];
        int64_t mn = min(prev, cur);
        int64_t mx = max(prev, cur);
        
        // no need for binary search, can just brute force this
        int exp_here = inf;
        for (int j = 0; j < 6; j++) {
            int64_t new_nr = int64_t(pow(mn, 1LL << j));
            if (new_nr >= mx) {
                exp_here = j;
                break;
            }
        }
        // cout << mn << " " << mx << " " << exp_here << endl;
        if (prev > cur && exp_here == inf) {
            ans = -1;
            break;
        }
        if (prev < cur && exp_here != inf && int64_t(pow(prev, 1LL << exp_here)) > cur) {
            // basically, if the previous ^ exp passes the current value, then
            // the exponent for the current value cannot be decreased by that value, only by the previous value
            // e.g. 2 vs 8: 2^4 = 16 > 8. 8 can't use a relative exponent of -2, only of -1
            exp_here--;
        }
        int exp_diff = prev > cur ? exp_here : -exp_here;
        exp_cnt = max(0, exp_cnt + exp_diff);
        ans += exp_cnt;
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
