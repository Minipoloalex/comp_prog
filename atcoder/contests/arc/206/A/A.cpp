#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    vector<int> cnt(n + 1);
    for (int ai: a) cnt[ai]++;

    int64_t ans = 0;
    for (int i = 0; i < n - 1; i++) {
        cnt[a[i]]--;
        if (i + 1 < n) {
            if (a[i + 1] == a[i]) continue;
            ans += n - 1 - i - cnt[a[i]];
        }
    }
    ans++;
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
