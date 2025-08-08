#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int64_t> a(n);
    for (auto &ai: a) cin >> ai;
    int64_t ans = 0;
    if (n == 1) {
        ans = 1;
    }
    else {
        sort(a.begin(), a.end());
        int64_t mx = a.back();
        int64_t g = 0;
        for (int i = 0; i < n - 1; i++) {
            // or mx - a[i] (it's the same thing: because of euclidean gcd thing)
            int64_t diff = a[i + 1] - a[i];
            g = gcd(g, diff);
        }
        for (int i = 0; i < n; i++) {
            ans += (mx - a[i]) / g;
        }
        int64_t mid_val = INT_MAX;
        for (int i = 0; i < n - 1; i++) {
            int64_t diff = a[i + 1] - a[i];
            if (diff > g) {
                mid_val = a[i + 1] - g;
            }
        }
        int64_t mn_to_add = INT_MAX;
        if (mid_val != INT_MAX) {
            mn_to_add = min(mn_to_add, (mx - mid_val) / g);
        }
        else {
            // doesn't make a difference to consider the min
            // because we know there's no middle value: we'll have to add n anyways

            // int64_t mn = a.front();
            // int64_t new_nr = mn - g;
            // mn_to_add = min({mn_to_add, int64_t(n), (mx - new_nr) / g});


            // a(n+1) = mx + g -> ans += n
            mn_to_add = min<int64_t>(mn_to_add, n);
        }
        ans += mn_to_add;
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
