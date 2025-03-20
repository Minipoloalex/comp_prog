#include <bits/stdc++.h>
using namespace std;

void solve() {
    int64_t n, P, l, t;
    cin >> n >> P >> l >> t;
    int64_t per_day = l + t * 2;
    int64_t needed = P / per_day;
    // this day may not need 2 full tasks
    int64_t need_tasks = needed * 2;
    int64_t rest = P - needed * per_day;
    if (rest <= l) {
        needed++;
    }
    else if (rest <= l + t) {
        needed++;
        need_tasks++;
    }
    else {
        needed++;
        need_tasks += 2;
    }
    int64_t max_tasks = (n + 6) / 7;
    if (need_tasks > max_tasks) {   // more tasks than days allow
        per_day = l;
        P -= t * max_tasks;
        needed = max((P + per_day - 1) / per_day, (max_tasks + 1) / 2);
    }
    cout << n - needed << '\n';
}

void better_solve() {
    int64_t n, P, l, t;
    cin >> n >> P >> l >> t;
    int64_t max_tasks = (n + 6) / 7;
    auto possible = [&](int days) {
        int64_t practical = min(max_tasks * t, days * 2 * t);
        int64_t total = practical + days * l;
        return total >= P;
    };
    int lo = 0, hi = (int) n;
    while (lo < hi) {
        int m = lo + (hi - lo) / 2;
        if (possible(m)) {
            hi = m;
        }
        else {
            lo = m + 1;
        }
    }
    // cout << lo << '\n';
    cout << n - lo << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--) {
        better_solve();
    }
    return 0;
}
