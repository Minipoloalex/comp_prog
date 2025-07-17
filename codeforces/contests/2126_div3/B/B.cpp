#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    int cnt = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == 0) cnt++;
        else cnt = 0;

        if (cnt == k) {
            i++;    // skip a day
            cnt = 0;
            ans++;
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
