#include <bits/stdc++.h>
using namespace std;

const int MAX_CI = int(2e5);

void solve() {
    int n, y;
    cin >> n >> y;
    vector<int> c(n);
    for (auto &ci: c) cin >> ci;
    int mx = *max_element(c.begin(), c.end());
    if (mx == 1) {
        cout << n << '\n';
        return;
    }

    vector<int> cnt(MAX_CI + 1);
    for (int ci: c) cnt[ci]++;

    vector<int> pref(MAX_CI + 1);
    for (int i = 1; i <= MAX_CI; i++) {
        pref[i] = pref[i - 1] + cnt[i];
    }
    auto test = [&](int x) {
        int64_t ans = 0;
        for (int i = 1; i <= (mx + x - 1) / x; i++) {
            int r = min(i * x, MAX_CI);
            int l = min((i-1) * x + 1 - 1, MAX_CI);
            int how_many = pref[r] - pref[l];
            ans -= max(0, how_many - cnt[i]) * 1LL * y;
            ans += 1LL * i * how_many;
        }
        return ans;
    };
    int64_t ans = INT64_MIN;
    for (int x = 2; x <= mx; x++) {
        ans = max(ans, test(x));
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
