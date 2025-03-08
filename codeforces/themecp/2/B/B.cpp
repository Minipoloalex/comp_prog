#include <bits/stdc++.h>
using namespace std;

void better_solve() {
    int n;
    cin >> n;
    vector<int64_t> h(n);
    for (auto &x: h) cin >> x;
    int64_t ans = h.back();
    for (int i = n - 2; i >= 0; i--) {
        if (h[i] <= ans) ans++;
        else {
            // h[i] > ans
            ans = h[i];
        }
    }
    cout << ans << '\n';
}

void solve() {
    int n;
    cin >> n;
    vector<int> h(n);
    for (auto &x: h) cin >> x;
    int64_t ans = h.back();
    int64_t cnt = ans;
    for (int i = n - 2; i >= 0; i--) {
        int64_t cur = h[i];
        if (cur > cnt) {
            ans = max(ans, cur);
            cnt = cur;
        }
        else {
            // assert(cur <= prev);
            int64_t value = cnt - (cur - 1) + cur;
            cnt = value;
            if (value > ans) {
                ans = value;
            }
        }
    }
    cout << ans << '\n';
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
