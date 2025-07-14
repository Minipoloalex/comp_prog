#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int64_t> p(2*n);
    for (auto &pi: p) cin >> pi;

    if (n == 1) {
        cout << abs(p[1] - p[0]) << '\n';
        return;
    }

    int64_t ans = INT64_MAX;
    if (n == 2) {
        int64_t cur = 0;
        for (int i = 0; i < 2 * n; i++) {
            cur += abs(p[i] - 2);
        }
        ans = min(ans, cur);
    }

    int64_t cur = 0;
    for (int i = 0; i < 2*n; i++) {
        cur += abs(p[i]);
    }
    ans = min(ans, cur);

    if (n % 2 == 0) {
        int64_t target = n;
        cur = 0;
        for (int i = 0; i < 2*n; i++) {
            cur += abs(p[i] + 1);   // p[i] - (-1)
        }
        for (int i = 0; i < 2 * n; i++) {
            ans = min(ans, cur - abs(p[i] + 1) + abs(target - p[i]));
        }
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
