#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, c;
    cin >> n >> c;
    vector<int64_t> a(n);
    for (auto &ai: a) cin >> ai;
    sort(a.rbegin(), a.rend());
    int ans = n;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] * (1 << cnt) <= c) {
            cnt++;
        }
    }
    cout << ans - cnt << '\n';
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
