#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    vector<int> cnt(n);
    int64_t cur = 0, ans = 0;
    cnt[0] = 1;
    for (int i = 0; i < n; i++) {
        cur += a[i];
        cur %= n;
        cur += n;
        cur %= n;

        ans += cnt[cur];
        cnt[cur]++;
    }
    cout << ans << '\n';
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
